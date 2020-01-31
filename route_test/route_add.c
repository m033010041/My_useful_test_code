#include <sys/types.h>
#include <sys/socket.h>
#include <net/route.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int addNullRoute(unsigned int gateway, char * ifname)
{
   // create the control socket.
   int fd = socket( PF_INET, SOCK_DGRAM, IPPROTO_IP );

   struct rtentry route;
   memset( &route, 0, sizeof( route ) );

   // set the gateway to 0.
   struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = gateway;

   // set the host we are rejecting.
   addr = (struct sockaddr_in*) &route.rt_dst;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;

   // Set the mask. In this case we are using 255.255.255.255, to block a single
   // IP. But you could use a less restrictive mask to block a range of IPs.
   // To block and entire C block you would use 255.255.255.0, or 0x00FFFFFFF
   addr = (struct sockaddr_in*) &route.rt_genmask;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;

   // These flags mean: this route is created "up", or active
   // The blocked entity is a "host" as opposed to a "gateway"
   // The packets should be rejected. On BSD there is a flag RTF_BLACKHOLE
   // that causes packets to be dropped silently. We would use that if Linux
   // had it. RTF_REJECT will cause the network interface to signal that the
   // packets are being actively rejected.
   route.rt_flags = RTF_UP | RTF_GATEWAY;
   route.rt_metric = 0;

   route.rt_dev = ifname;
   // this is where the magic happens..
   if ( ioctl( fd, SIOCADDRT, &route ) )
   {
      close( fd );
      return -1;
   }

   // remember to close the socket lest you leak handles.
   close( fd );
   return 0;
}

int delNullRoute(unsigned int gateway, char * ifname)
{
   int fd = socket( PF_INET, SOCK_DGRAM, IPPROTO_IP );

   struct rtentry route;
   memset( &route, 0, sizeof( route ) );

   struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = gateway;

   addr = (struct sockaddr_in*) &route.rt_dst;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;

   addr = (struct sockaddr_in*) &route.rt_genmask;
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = INADDR_ANY;

   route.rt_flags = RTF_UP | RTF_GATEWAY;
   route.rt_metric = 0;

   route.rt_dev = ifname;
   // this time we are deleting the route:
   if ( ioctl( fd, SIOCDELRT, &route ) )
   {
      close( fd );
      return -1;
   }

   close( fd );
   return 0;
}

int main(int argc, char ** argv)
{
	if (!strcmp(argv[1], "ADD")) {
		if (!addNullRoute(inet_addr(argv[2]), argv[3]))
		    printf("ADD successful\n");
    	else
		    printf("ADD failed\n");
	} else {
		if (!delNullRoute(inet_addr(argv[2]), argv[3]))
		    printf("DEL successful\n");
    	else
		    printf("DEL failed\n");
	}
        return 0;
}
