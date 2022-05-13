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


bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}

int length = 1000;
int width = 650;
 
int main(){
    
    ALLEGRO_DISPLAY *display;
    const float FPS = 60.0;
    const float frameFPS = 60.0;
 
    if(!al_init()) return -1;
    display = al_create_display(length,width); 
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
    
   
   
   
    
    ALLEGRO_FONT *font1 = al_load_font("Minecrafter_3.ttf", 15, 0);
    ALLEGRO_FONT *mcfont = al_load_font("Minecrafter_3.ttf", 30, 0);
    
    
   
    
    ALLEGRO_TIMER *timer2 = al_create_timer(1.0 / 10);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 10);
    ALLEGRO_TIMER *frameTimer = al_create_timer(1.0 / frameFPS);
    ALLEGRO_TIMER *VREME = al_create_timer(1);
    ALLEGRO_KEYBOARD_STATE keyState;
    
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(timer2));
    al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(VREME));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_start_timer(timer);
    al_start_timer(timer2);
    al_start_timer(frameTimer);
    al_start_timer(VREME);
    srand (time(NULL));
    
   
    int timeS = 0;
    int timeF = 0;
    
    enum Direction { DOWN, LEFT, RIGHT, UP };
    
   
    int dir = RIGHT;
    int score=1;
    int lastX;
    int lastY;
    
    int coinX=40*(rand()%20);
    int coinY=40*(rand()%15);
    
    
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
                  
                  // change the position
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
                      //check for collision            
           if(collide(x,y,x+20,y+20,coinX,coinY,coinX+20,coinY+20)){ 
                       score++;
                       //al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL); 
                       coinX=40*(rand()%20);
                       coinY=40*(rand()%15);
                     
                       
                       }
                       
                       
           //if the snake head touches the other part of the body dead is true
           if(menu==false){    
                
           for(int i=0;i<score;i++){
                   if(x==snakeX[i] && y==snakeY[i] && menu==false) dead=true;
                   }
           if(x<0  && menu==false) // y=(-1*y)
           {
           	x=length;
           }
           if(x>length  && menu==false) 
           {
           	x=length-x;
           } 
           if(y>width  && menu==false) 
           {
           	y=width-width;
           } 
           if(y<0  && menu==false) 
           {
           	y=width;
           }                
           }
           
           draw=true;
           
                                  }}
                                  
           //if dead show reset and show menu 
if(dead && menu==false){
         menu=true;
         timeF=timeS;
         x=0,y=0;
          timer=timer2;
           
         dead=false;
         dir=DOWN;
         }

          
          //Drawing                    
          if(draw==true){ 
                          draw=false;
                        if(menu){
                                 x=0,y=0;
                                   
                     al_draw_text(mcfont, al_map_rgb(100,50,250), 170, 100, 0,
                      "Press Enter to Start");
                     al_draw_text(mcfont, al_map_rgb(100,50,250), 205, 200, 0,
                      "Press Esc to Exit"); 
                      al_draw_textf(mcfont, al_map_rgb(250,0,250), 120, 350, 0,
                      "Coins: %i", score-1);
                  al_draw_textf(mcfont, al_map_rgb(250,0,250), 470, 350, 0,
                      "Time: %i sec", timeF);  
                       al_draw_textf(font1, al_map_rgb(250,0,250), 300, 50, 0,
                      "Go fast  : press F");
                   al_draw_textf(font1, al_map_rgb(250,0,250), 700, 50, 0,
                      "Go slow press S"); 
                      }
                        else{                   
                 
                // al_draw_bitmap_region(coin1, curF /* frameW*/, 0, frameW, frameH, coinX, coinY, 0);
                  al_draw_filled_rounded_rectangle(coinX,coinY,coinX+20,coinY+20,10,10,al_map_rgb(250,110,20));
                 for(int i=0;i<score;i++){
                
                al_draw_filled_rounded_rectangle(snakeX[i],snakeY[i],snakeX[i]+20,snakeY[i]+20,5,5,al_map_rgb(20,110,20));
                
                                                 }
                                              //go fast or slow
                  if(al_key_down(&keyState, ALLEGRO_KEY_F))
				  { 
					 timer=frameTimer; 
				   }
				  else if(al_key_down(&keyState, ALLEGRO_KEY_S))
				  {
					  timer=timer2;
				  }                               
                                                                    
                
                al_draw_filled_rounded_rectangle(x,y,x+20,y+20,10,10,al_map_rgb(250,70,20));
                 al_draw_textf(font1, al_map_rgb(250,0,250), 5, 5, 0,
                      "Coins: %i", score-1);
                  al_draw_textf(font1, al_map_rgb(250,0,250), 900-10, 5, 0,
                      "Time: %i", timeS);    
                      al_draw_textf(font1, al_map_rgb(250,0,250), 300, 5, 0,
                      "Go fast  : press F");
                   al_draw_textf(font1, al_map_rgb(250,0,250), 700, 5, 0,
                      "Go slow press S");  }
                           
                  al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));                
                                  }                         
                                  
           
                      
                               
                   }//while
 


   al_destroy_display(display);
   al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
   return 0;
}

