#include "PhantomSDL.h"

CSystem *System = CSystem::getInstance();

class Prueba : public PhantomSDL_CINSTANCE
    {
    public:
    float theta;
    CLog *mLog;
    CKeyboard *mKeyIn;

    Prueba() {  mLog = CLog::getInstance(); mKeyIn = CKeyboard::getInstance();};
    ~Prueba() { }

    void createEvent() {
        theta = 0.0f;
        mLog->write(1,"createEvent de instancia de Prueba, clase derivada de CInstancia, ejecutado con exito.");
        }

    void destroyEvent(){
        mLog->write(1,"destroyEvent de instancia de Prueba, clase derivada de CInstancia, ejecutado con exito.");
        }

    void drawEvent(){

        }

    void stepEvent(){
        theta += 1.5f;
        bool visible = getVisible();
        if(mKeyIn->getKey(SDLK_SPACE,true)) setVisible(!visible);
        if(mKeyIn->getKey(SDLK_f)) System->getSDL()->switchFullscreen();
        }
    };

int main(int argc, char * argv[])
    {
    System->getSDL()->init(SDL_INIT_VIDEO,SDL_HWSURFACE,800,600,32);

    const int MagicNumber = 1;

    Prueba *obj[MagicNumber];

    for(int i=0; i<MagicNumber; i++)
        {
        obj[i] = new Prueba;
        obj[i]->setVisible(true);
        System->getInstanceHandler()->addInstance(obj[i]);
        }

    while(System->isRunning())
        {
        System->run();
        }
    System->erase();

    return 0;
    };
