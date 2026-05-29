#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define DEVICE "/dev/gpio_led"

#define MYGPIO_MAGIC 'G'
#define GPIO_SET_HIGH _IO(MYGPIO_MAGIC, 1)
#define GPIO_SET_LOW  _IO(MYGPIO_MAGIC, 2)
#define GPIO_TOGGLE   _IO(MYGPIO_MAGIC, 3)

int main()
{
        int fd;
        char buffer[2];
    fd=open(DEVICE, O_RDWR);
    if(fd<0)
    {
        printf("\nFailed to open device ");
        return -1;
    }

printf("\nDevice opened Successfully");


while(1){
    printf("\n1.Set GPIO high\n2.Set GPIO low\n3.Toggle GPIO\n4.Read GPIO\n5.Exit\n\tEnter your option: ");
    int c;
    scanf("%d",&c);


    switch(c)
    {
    case 1:ioctl(fd,GPIO_SET_HIGH);
            printf("\nGPIO set high");
            break;

    case 2:ioctl(fd,GPIO_SET_LOW);
            printf("\nGPIO set low");
            break;

    case 3:ioctl(fd,GPIO_TOGGLE);
            printf("\nGPIO toggled");
            break;

    case 4:memset(buffer,0,sizeof(buffer));
            read(fd,buffer,1);
            printf("GPIO state %c\n",buffer[0]);
            break;

    case 5:close(fd);
            return 0;

    default:
        printf("Invalid option\n");
    }
    

}
close(fd);
return 0;
}