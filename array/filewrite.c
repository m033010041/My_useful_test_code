#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CONFIG_FILE "8168FBEF.CFG"

int startsWith(const char *pre, const char *str)
{
        size_t lenpre = strlen(pre);
	size_t lenstr = strlen(str);
        return (lenstr < lenpre) ? 0 : ((strncmp(pre, str, lenpre) == 0) ? 1 : 0);
}

/* check_efuse_mac()
 * @return:
 *    -1: mac is wrong or open file error, or system call error
 *    mac address:
 */
int read_efuse_mac(int phy)
{
	FILE *fd = NULL;
	char buf[2048];
	int macaddr = 0;
	unsigned int mac[6] = {0};
	const char *weintek_mac = "NODEID = 00 0C 26";
	char *dump_mac;

	/* read mac info from efuse */
	switch(phy){
	case 0:
		if(system("PG8168.EXE /efuse /# 1 /r > MAC0.TXT")) {
			printf("MAC1 syscall error\n");
			return -1;
		}
		fd = fopen("mac0.txt", "r");
		break;
	case 1:
		fd = fopen("MAC1.TXT", "rb");
		break;
	default:
		break;
	}

	if(fd == NULL)
		return -1;

	while (NULL != fgets(buf, sizeof(buf), fd)) {
		dump_mac = strstr(buf, "NODEID");

		if(dump_mac != NULL)
		{
                        memset(mac, 0, sizeof(mac));
                        sscanf(&dump_mac[9], "%02X %02X %02X %02X %02X %02X",
					&mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
			printf("getmac1: %02X, %02X, %02X, %02X, %02X, %02X\n",
					mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
                        /*
			fclose(fd);

			if(startsWith(weintek_mac, dump_mac))
			{
				sscanf(dump_mac+9, "%02X %02X %02X %02X %02X %02X",
				   &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

				printf("getmac1: %02X, %02X, %02X, %02X, %02X, %02X\n",
					mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

			}
                        */
		}
	}

	macaddr = (mac[3]<<16) + (mac[4]<<8) + mac[5];
	fclose(fd);

	return macaddr;
}

int read_pg8168_config(void)
{
	FILE *fd = NULL;
	char buf[128] = {0};
	unsigned int mac[6] = {0};
	char *dump_mac = NULL;
	const char *weintek_mac = "NODEID = 00 0C 26";
	int i=0;

	fd = fopen(CONFIG_FILE, "r");

	if(fd == NULL)
	{
		printf("open config file error\n");
		return -1;
	}

	if((fgets(buf, sizeof(buf), fd)) != NULL)
	{
		/* find NODE_ID*/
		dump_mac = strstr(buf, "NODEID");

		if(dump_mac != NULL)
		{
			sscanf(dump_mac+9, "%02X %02X %02X %02X %02X %02X",
					&mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
			printf("getcfgmac: %02X, %02X, %02X, %02X, %02X, %02X\n",
					mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			fclose(fd);
		}
	}
	else
		fclose(fd);
	return (mac[3]<<16) + (mac[4]<<8) + mac[5];
}

void error_log(char * cmd)
{
	FILE *fp = NULL;
	int ret;

	fp = fopen("ERRLOG.txt", "wb");

	if (fp == NULL) {
		printf("write ERRLOG: open file error !!\n");
		return;
	}

        fputs(cmd, fp);
        fclose(fp);
        return;
}

int main()
{
        char cmd[256] = {0};
        int ret, a, b;

        a = read_efuse_mac(1);
        b = read_pg8168_config();
        printf("a=%d, b=%d\n", a, b);
        if ((read_efuse_mac(1) & 0xFFFFFF) != (read_pg8168_config()-1 & 0xFFFFFF)) {
                error_log("error occurred!!\n");
                sprintf(cmd, "mac1=%d, cfg=%d\n", read_efuse_mac(1), read_pg8168_config());
                error_log(cmd);
        } else {
                printf("check successful, mac1=%d, cfg=%d\n", read_efuse_mac(1), read_pg8168_config());
        }
        return 0;
}
