struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

struct Bullet {
    float xpos;
    float ypos;
    float zpos;
    float xrot;
    float yrot;
    float zrot;
    int fired;
    int player;
};
typedef struct Bullet Bullet;

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




void PlayerMove();
void WorldMove(Bullet * bullets,char ** map,Turret * turrets,float xpos,float ypos,float zpos,int *hp);
void Map(char** map, int * texture);
void CheckWin();
void Menu();
void MapGen(char ** map,Turret * turrets);
void LoadGLTextures(int * texture);
int  ImageLoad(char *filename, Image *image);
