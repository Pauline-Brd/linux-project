//AUTEURS : Pauline Bernard, Cherine Seo, Edouard Mignien

#include <cairo.h>
#include <gtk/gtk.h>
#include <wiringPi.h>

#define RED1 14
#define RED2 13

#define YELLOW1 12
#define YELLOW2 3

#define GREEN1 0
#define GREEN2 7

gboolean update = FALSE;

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
    gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}
//Setup définit toutes les Leds en entrée
void setup()
{
  if(wiringPiSetup() == -1) {
                printf("setup wiringPi failed !\n");
  }
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(YELLOW2, OUTPUT);

}
//do_drawing est le sous-programme d'affichage sur l'interface graphique
void do_drawing(cairo_t *cr)
{
  //Chemin piétons
  cairo_set_source_rgb(cr, 0.98, 0.81, 0.55);
  cairo_rectangle(cr, 0, 300, 800, 200);
  cairo_fill(cr);

  //Route
  cairo_set_source_rgb(cr, 0.08, 0.08, 0.08);
  cairo_move_to(cr, 250, 200);
  cairo_line_to(cr, 0, 850);
  cairo_line_to(cr, 800, 850);
  cairo_line_to(cr, 550, 200);
  cairo_close_path(cr);

  //Lignes route
  cairo_move_to(cr, 250, 200);
  cairo_line_to(cr, 0, 850);
  cairo_line_to(cr, 800, 850);
  cairo_line_to(cr, 550, 200);
 cairo_close_path(cr);

  //Passage piéton
  cairo_set_source_rgb(cr, 0.83, 0.79, 0.79);
  cairo_move_to(cr, 220, 300);
  cairo_line_to(cr, 200, 500);
  cairo_line_to(cr, 320, 500);
  cairo_line_to(cr, 300, 300);
  cairo_close_path(cr);

  //Feu voitures
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
  cairo_rectangle(cr, 700, 250, 10, 270);
  cairo_fill(cr);

  cairo_rectangle(cr, 680, 150, 50, 100);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.45, 0.23, 0.23);
cairo_arc(cr, 705, 170, 15, 0, 10);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.69, 0.6, 0.17);
  cairo_arc(cr, 705, 200, 15, 0, 10);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.21, 0.35, 0.21);
  cairo_arc(cr, 705, 230, 15, 0, 10);
  cairo_fill(cr);

  //Feu piétons
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
  cairo_rectangle(cr, 200, 100, 10, 190);
  cairo_fill(cr);

  cairo_rectangle(cr, 180, 0, 50, 100);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.45, 0.23, 0.23);
  cairo_arc(cr, 205, 20, 15, 0, 10);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.69, 0.6, 0.17);
  cairo_arc(cr, 205, 50, 15, 0, 10);
  cairo_fill(cr);

  cairo_set_source_rgb(cr, 0.21, 0.35, 0.21);
  cairo_arc(cr, 205, 80, 15, 0, 10);
  cairo_fill(cr);

  if((update==TRUE) && (digitalRead(RED1)==HIGH))//Si la Led RED1 est allumée
  {
         cairo_set_source_rgb(cr, 1, 0, 0); //On l'affiche sur la GUI
         cairo_arc(cr, 705, 170, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);

         cairo_set_source_rgb(cr, 0, 1, 0);//On affiche la Led GREEN1 de l'autre feu
         cairo_arc(cr, 205, 80, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);
  }
  if((update==TRUE) && (digitalRead(GREEN1)==HIGH))//Si la led GREEN1 est allumée
  {
         cairo_set_source_rgb(cr, 0, 1, 0);//On l'affiche sur la GUI
         cairo_arc(cr, 705, 230, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);

         cairo_set_source_rgb(cr, 1, 0, 0);//On affiche la led RED1 de l'autre feu
         cairo_arc(cr, 205, 20, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);

  }
  if((update==TRUE) && (digitalRead(YELLOW1)==HIGH))//si la led YELLOW1 est allumée
  {
         cairo_set_source_rgb(cr, 1, 0.83, 0);//On l'affiche sur la GUI
         cairo_arc(cr, 705, 200, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);

         cairo_set_source_rgb(cr, 1, 0, 0);//On affiche la led RED1 de l'autre feu
         cairo_arc(cr, 205, 20, 15, 0, 10);
         cairo_stroke_preserve(cr);
         cairo_fill(cr);
  }
  if((update==TRUE) && (digitalRead(YELLOW2)==HIGH))//Si le mode danger (bouton appuyé) est activé
  {
         cairo_set_source_rgb(cr, 1, 0, 0);//On affiche un message de prévention
         cairo_move_to(cr, 400, 20);
         cairo_show_text(cr, "ATTENTION, FEU PIETONS EN PANNE");
  }

}
//clicked est le sous-programme de mise à jour de la fenêtre graphique
static gboolean clicked(GtkWidget *widget, gpointer *data)
{
        update = TRUE;
        gtk_widget_queue_draw(widget);//On refresh
        return TRUE;
}
int main(int argc, char *argv[])
{
  setup();
  GtkWidget *window;
  GtkWidget *darea;
  GtkWidget *fixed;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//On crée la fenêtre

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//Au centre de l'écran
  gtk_window_set_default_size(GTK_WINDOW(window), 850, 900);//Dimensions de la fenêtre
  gtk_window_set_title(GTK_WINDOW(window), "INTERFACE GRAPHIQUE");//Nom de la fenêtre


  darea = gtk_drawing_area_new();//On crée une nouvelle zone de dessin
  gtk_widget_set_size_request(darea, 800, 850);//dimensions

  fixed = gtk_fixed_new();//Widget fixed de GTK

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);//On dessine sur la zone
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);//On la détruit

  gtk_fixed_put(GTK_FIXED(fixed), darea, 0, 20);//On l'ajoute au fixed

  button = gtk_button_new_with_label("REFRESH");//on crée un bouton
  gtk_widget_set_size_request(GTK_WIDGET(button), 20, 30);//Dimensions

  gtk_fixed_put(GTK_FIXED(fixed), button, 0, 0);//On l'ajoute au fixed
  gtk_container_add(GTK_CONTAINER(window), fixed);//On greffe le fixed à la fenêtre

  g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(clicked), NULL);//on connecte le bouton avec le sous-programme clicked
  gtk_widget_show_all(window);//On affiche la page
  gtk_main();//Boucle
  return 0;
}
