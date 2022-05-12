#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
 #include <allegro5/allegro_primitives.h>
#include <time.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h> 
#include <stdio.h>

//using namespace std;

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}

int dolzina = 1000;
int visina = 650;
 
int main(){
    
    ALLEGRO_DISPLAY *display;
    ALLEGRO_SAMPLE *MUZ = NULL;
    const float FPS = 60.0;
    const float frameFPS = 15.0;
 
    if(!al_init()) return -1;
    display = al_create_display(dolzina,visina); 
    if(!display) return -1;
    al_set_window_position(display, 200, 0);
   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

    
    bool done = false, active = false;
    bool draw = true;
    int x = 0, y = 0, moveSpeed = 5;
    
    
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    MUZ = al_load_sample("coin1.flac"); 
     if (!MUZ){
      printf( "Audio clip sample not loaded!\n" ); 
      //return -1;
   }
    ALLEGRO_BITMAP *glava = al_load_bitmap("glava.png");
    ALLEGRO_BITMAP *telo = al_load_bitmap("telo.png");
    
    ALLEGRO_FONT *font1 = al_load_font("Minecrafter_3.ttf", 15, 0);
    ALLEGRO_FONT *mcfont = al_load_font("Minecrafter_3.ttf", 30, 0);
    ALLEGRO_BITMAP *coin1 = al_load_bitmap("coin.png");
    
   
    
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 10);
    ALLEGRO_TIMER *frameTimer = al_create_timer(1.0 / frameFPS);
    ALLEGRO_TIMER *VREME = al_create_timer(1);
    ALLEGRO_KEYBOARD_STATE keyState;
    
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(VREME));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_start_timer(timer);
    al_start_timer(frameTimer);
    al_start_timer(VREME);
    srand (time(NULL));
    
    const int maxF = 8;
    int curF = 0;
    int frameC = 0;
    int frameD = 2;
    int frameW = 40;
    int frameH = 40;
    int timeS = 0;
    int timeF = 0;
    
    enum Direction { DOWN, LEFT, RIGHT, UP };
    
    bool sdasda;
    int dir = RIGHT;
    int score=1;
    int lastX;
    int lastY;
    
    int coinX=40*(rand()%20);
    int coinY=40*(rand()%15);
    
    //int snakeT[50];
    for(int i=0;i<=50;i++){
            //snakeT[i]=0;
            }
    int snakeX[1000], snakeY[1000];
    
    bool menu = true;
    bool dead = false;
     while(!done){ 
        
        
        
         lastX=x;
         lastY=y;
                   
                   
          ALLEGRO_EVENT events;
          al_wait_for_event(event_queue, &events);   
          
          
          if(events.type == ALLEGRO_EVENT_KEY_UP)
          {
            switch(events.keyboard.keycode){
                  case ALLEGRO_KEY_ESCAPE:
                       done = true;
                       break;
                   case ALLEGRO_KEY_ENTER:
                       if(menu) menu=false, score=1, timeS=0, x=0, y=0;
                       break;                                      
                                            }             
                         }                                              
           else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                      done = true;
                      
           if(events.type == ALLEGRO_EVENT_TIMER){
           if(events.timer.source == VREME) timeS++;                
           if(events.timer.source == timer){
             
                  al_get_keyboard_state(&keyState);
                  if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && dir!=LEFT)
                  dir=RIGHT;                  
                 else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT) && dir!=RIGHT)
                  dir=LEFT; 
                 else if(al_key_down(&keyState, ALLEGRO_KEY_UP) && dir!=DOWN)
                  dir=UP; 
                 else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN) && dir!=UP)
                  dir=DOWN;
                  else if(al_key_down(&keyState, ALLEGRO_KEY_A))
                  score++;
                  else if(al_key_down(&keyState, ALLEGRO_KEY_ENTER) && menu==true)
                  menu=false, score=1, timeS=0, x=0, y=0;  
           if(menu==false){
           if(score!=0){             
           for(int i=score;i>0;i--){              
              snakeX[i]=snakeX[i-1];
              snakeY[i]=snakeY[i-1];          
           } 
           snakeX[0]=lastX;
           snakeY[0]=lastY;  
           } }
            
            switch(dir){
                        case RIGHT: x=x+8;
                        break;
                        case LEFT: x=x-8;
                        break; 
                        case UP: y=y-8;
                        break; 
                        case DOWN: y=y+8;
                        break;      
                        }
               int X=snakeX[0], Y=snakeY[0]; 
                                  
           if(collide(x,y,x+20,y+20,coinX,coinY,coinX+20,coinY+20)){ 
                       score++;
                       //al_play_sample(MUZ, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL); 
                       coinX=40*(rand()%20);
                       coinY=40*(rand()%15);
                       //snakeT[score]=1;
                       }
           
           if(menu==false){            
           for(int i=0;i<score;i++){
                   if(x==snakeX[i] && y==snakeY[i] && menu==false) dead=true;
                   }
           if(x<0 || x>=dolzina || y<0 || y>=visina && menu==false) dead=true;                    
           }
           
           draw=true;
           
                                  }}
            if(++frameC >= frameD){
               if(++curF >= maxF)
                  curF = 0;
                  
            frameC = 0;    
                        }                      

if(dead && menu==false){
         menu=true;
         timeF=timeS;
         x=0,y=0;
          for(int i=0;i<=50;i++){
            //snakeT[i]=0;
            }
         dead=false;
         dir=DOWN;
         }

          
                              
          if(draw==true){ 
                          draw=false;
                        if(menu){
                                 x=0,y=0;
                                   for(int i=0;i<=50;i++){
            //snakeT[i]=0;
            }
                     al_draw_text(mcfont, al_map_rgb(100,50,250), 170, 100, 0,
                      "Press Enter to Start");
                     al_draw_text(mcfont, al_map_rgb(100,50,250), 205, 200, 0,
                      "Press Esc to Exit"); 
                      al_draw_textf(mcfont, al_map_rgb(250,0,250), 120, 350, 0,
                      "Coins: %i", score-1);
                  al_draw_textf(mcfont, al_map_rgb(250,0,250), 470, 350, 0,
                      "Time: %i sec", timeF);   
                      }
                        else{                   
                 //al_draw_bitmap(coin1, coinX, coinY, 0);
                // al_draw_bitmap_region(coin1, curF /* frameW*/, 0, frameW, frameH, coinX, coinY, 0);
                  al_draw_filled_rounded_rectangle(coinX,coinY,coinX+20,coinY+20,10,10,al_map_rgb(250,110,20));
                 for(int i=0;i<score;i++){
                // al_draw_bitmap(telo, snakeX[i], snakeY[i], 0); //draw bitmap at those locations of the array
                al_draw_filled_rounded_rectangle(snakeX[i],snakeY[i],snakeX[i]+20,snakeY[i]+20,5,5,al_map_rgb(20,110,20));
                //i+=2;
                                                 }
                                                                    
                // al_draw_bitmap(glava, x, y, 0); 
                al_draw_filled_rounded_rectangle(x,y,x+20,y+20,10,10,al_map_rgb(250,70,20));
                 al_draw_textf(font1, al_map_rgb(250,0,250), 5, 5, 0,
                      "Coins: %i", score-1);
                  al_draw_textf(font1, al_map_rgb(250,0,250), 900-10, 5, 0,
                      "Time: %i", timeS);     }
                                   
                  al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));                
                                  }                         
                                  
           
                      
                               
                   }//while
 

 al_destroy_sample(MUZ);
   al_destroy_display(display);
   al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
   return 0;
}
