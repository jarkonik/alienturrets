
#include <stdlib.h>
#include <time.h>

struct Turret {
    float xpos;
    float ypos;
    float zpos;
    float xrot;
    float yrot;
    float zrot;
    int existing;
};
typedef struct Turret Turret;

void MapGen(char ** map,Turret * turrets)
{
	srand (time(NULL));
	int i,j,k,choice;
	for (i=0;i<=48;i++)
	{
		for  (j=0;j<=48;j++)
		{
		if (j%2==0) map[i][j]=1;
		if (i%2==0) map[i][j]=1;
		//map[i][j]=1;
		}
	}

	
	for (i=1;i<=48;i+=2)
	{
		
		for  (j=1;j<=48;j+=2)
		{
			choice=rand()%2;
			if (choice==0)
			{
				if ((j+1<48) && (map[i][j+1]!=0)) map[i][j+1]=0;
					else if ((i-1>0) && (map[i-1][j]!=0)) map[i-1][j]=0;
			}

			if (choice==1)
			{
				if ((i-1>0) && (map[i-1][j]!=0)) map[i-1][j]=0;
					else if ((j+1<48) && (map[i][j+1]!=0)) map[i][j+1]=0;
			}
		}
	
	}
	
	//Add turrets

		
						for (i=1;i<100;i++)
						{	
						
							if (turrets[i].existing==0)
							{
								j=(rand()%43)+5;
								k=(rand()%43)+5;
							
								if (map[k][j]==0)
								{
									turrets[i].xpos=j*3.3-75;
									turrets[i].ypos=-1;
	 								turrets[i].zpos=k*3.3-75;
									turrets[i].xrot=0;
									turrets[i].yrot=0;
									turrets[i].zrot=0;
									turrets[i].existing=1;
									//break;
								}
							}
						}
				
			
		
		//Carve center hall

		for (i=12;i<=36;i++)
		{
			for (j=12;j<=36;j++)
			{
			map[i][j]=0;
			}
		}


		//Carve halls for starting end ending point
		for (i=1;i<=5;i++)
		{
			for (j=1;j<=5;j++)
			{
			map[i][j]=0;
			}
		}
			for (i=47;i>=42;i--)
		{
			for (j=47;j>=42;j--)
			{
			map[i][j]=0;
			}
		}
		
		
	


}
