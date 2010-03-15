/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_win_main (void)
{
  GtkWidget *win_main;
  GtkWidget *alignment_main;
  GtkWidget *scrolledwindow_main;
  GtkWidget *layout_main;
  GtkWidget *_filemenu_main;
  GtkWidget *menuitem_file;
  GtkWidget *menuitem_file_menu;
  GtkWidget *open;
  GtkWidget *clean_img;
  GtkWidget *separatormenuitem1;
  GtkWidget *quitter;
  GtkWidget *menuitem_eclairage;
  GtkWidget *menuitem_eclairage_menu;
  GSList *simple_group = NULL;
  GtkWidget *simple;
  GtkWidget *lambert;
  GtkWidget *phong;
  GtkWidget *blinn_phong;
  GtkWidget *menuitem_texture;
  GtkWidget *menuitem_texture_menu;
  GtkWidget *perlin;
  GtkWidget *menuitem_options;
  GtkWidget *menuitem_options_menu;
  GtkWidget *antialiasing;
  GtkWidget *menuitem_help;
  GtkWidget *menuitem_help_menu;
  GtkWidget *log;
  GtkWidget *copying;
  GtkWidget *s__parateur1;
  GtkWidget *about;
  GtkWidget *frame_scene;
  GtkWidget *alignment2;
  GtkWidget *scrolledwindow2;
  GtkWidget *viewport_scene;
  GtkWidget *scrolledwindow3;
  GtkWidget *textview_scene;
  GtkWidget *lbl_frame;
  GtkWidget *entry_open;
  GtkWidget *lbl_open;
  GtkWidget *cmd_open;
  GtkWidget *lbl_img_name;
  GtkWidget *entry_img_name;
  GtkWidget *cmd_start;
  GtkWidget *chk_parallel;
  GtkWidget *entry_parallel;
  GtkWidget *lbl_proc;
  GtkWidget *lbl_parallel;
  GtkWidget *textview_print;
  GtkWidget *lbl_generate;
  GtkWidget *chk_generate;
  GtkWidget *entry_sample;
  GtkWidget *lbl_samples;
  GtkWidget *img_logo;
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();

  win_main = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (win_main, 800, 600);
  gtk_window_set_title (GTK_WINDOW (win_main), _("KF-Ray GUI - Interface graphique pour KF-Ray"));
  gtk_window_set_resizable (GTK_WINDOW (win_main), FALSE);

  alignment_main = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment_main);
  gtk_container_add (GTK_CONTAINER (win_main), alignment_main);

  scrolledwindow_main = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow_main);
  gtk_container_add (GTK_CONTAINER (alignment_main), scrolledwindow_main);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow_main), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow_main), GTK_SHADOW_IN);

  layout_main = gtk_layout_new (NULL, NULL);
  gtk_widget_show (layout_main);
  gtk_container_add (GTK_CONTAINER (scrolledwindow_main), layout_main);
  gtk_layout_set_size (GTK_LAYOUT (layout_main), 400, 400);
  GTK_ADJUSTMENT (GTK_LAYOUT (layout_main)->hadjustment)->step_increment = 10;
  GTK_ADJUSTMENT (GTK_LAYOUT (layout_main)->vadjustment)->step_increment = 10;

  _filemenu_main = gtk_menu_bar_new ();
  gtk_widget_show (_filemenu_main);
  gtk_layout_put (GTK_LAYOUT (layout_main), _filemenu_main, 0, 0);
  gtk_widget_set_size_request (_filemenu_main, 800, 24);

  menuitem_file = gtk_menu_item_new_with_mnemonic (_("_Fichier"));
  gtk_widget_show (menuitem_file);
  gtk_container_add (GTK_CONTAINER (_filemenu_main), menuitem_file);

  menuitem_file_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_file), menuitem_file_menu);

  open = gtk_image_menu_item_new_from_stock ("gtk-open", accel_group);
  gtk_widget_show (open);
  gtk_container_add (GTK_CONTAINER (menuitem_file_menu), open);

  clean_img = gtk_menu_item_new_with_mnemonic (_("_Nettoyer images"));
  gtk_widget_show (clean_img);
  gtk_container_add (GTK_CONTAINER (menuitem_file_menu), clean_img);

  separatormenuitem1 = gtk_separator_menu_item_new ();
  gtk_widget_show (separatormenuitem1);
  gtk_container_add (GTK_CONTAINER (menuitem_file_menu), separatormenuitem1);
  gtk_widget_set_sensitive (separatormenuitem1, FALSE);

  quitter = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
  gtk_widget_show (quitter);
  gtk_container_add (GTK_CONTAINER (menuitem_file_menu), quitter);

  menuitem_eclairage = gtk_menu_item_new_with_mnemonic (_("_Eclairage"));
  gtk_widget_show (menuitem_eclairage);
  gtk_container_add (GTK_CONTAINER (_filemenu_main), menuitem_eclairage);

  menuitem_eclairage_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_eclairage), menuitem_eclairage_menu);

  simple = gtk_radio_menu_item_new_with_mnemonic (simple_group, _("_Sans"));
  simple_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (simple));
  gtk_widget_show (simple);
  gtk_container_add (GTK_CONTAINER (menuitem_eclairage_menu), simple);
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (simple), TRUE);

  lambert = gtk_radio_menu_item_new_with_mnemonic (simple_group, _("_Lambert"));
  simple_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (lambert));
  gtk_widget_show (lambert);
  gtk_container_add (GTK_CONTAINER (menuitem_eclairage_menu), lambert);
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (lambert), TRUE);

  phong = gtk_radio_menu_item_new_with_mnemonic (simple_group, _("_Phong"));
  simple_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (phong));
  gtk_widget_show (phong);
  gtk_container_add (GTK_CONTAINER (menuitem_eclairage_menu), phong);
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (phong), TRUE);

  blinn_phong = gtk_radio_menu_item_new_with_mnemonic (simple_group, _("_Blinn-Phong"));
  simple_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (blinn_phong));
  gtk_widget_show (blinn_phong);
  gtk_container_add (GTK_CONTAINER (menuitem_eclairage_menu), blinn_phong);
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (blinn_phong), TRUE);

  menuitem_texture = gtk_menu_item_new_with_mnemonic (_("_Textures"));
  gtk_widget_show (menuitem_texture);
  gtk_container_add (GTK_CONTAINER (_filemenu_main), menuitem_texture);

  menuitem_texture_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_texture), menuitem_texture_menu);

  perlin = gtk_check_menu_item_new_with_mnemonic (_("Perlin"));
  gtk_widget_show (perlin);
  gtk_container_add (GTK_CONTAINER (menuitem_texture_menu), perlin);
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (perlin), TRUE);

  menuitem_options = gtk_menu_item_new_with_mnemonic (_("_Avanc\303\251es"));
  gtk_widget_show (menuitem_options);
  gtk_container_add (GTK_CONTAINER (_filemenu_main), menuitem_options);

  menuitem_options_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_options), menuitem_options_menu);

  antialiasing = gtk_check_menu_item_new_with_mnemonic (_("Anti-aliasing"));
  gtk_widget_show (antialiasing);
  gtk_container_add (GTK_CONTAINER (menuitem_options_menu), antialiasing);

  menuitem_help = gtk_menu_item_new_with_mnemonic (_("_Info"));
  gtk_widget_show (menuitem_help);
  gtk_container_add (GTK_CONTAINER (_filemenu_main), menuitem_help);

  menuitem_help_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_help), menuitem_help_menu);

  log = gtk_menu_item_new_with_mnemonic (_("Versions de KF-Ray"));
  gtk_widget_show (log);
  gtk_container_add (GTK_CONTAINER (menuitem_help_menu), log);

  copying = gtk_menu_item_new_with_mnemonic (_("License GNU GPL v3"));
  gtk_widget_show (copying);
  gtk_container_add (GTK_CONTAINER (menuitem_help_menu), copying);

  s__parateur1 = gtk_separator_menu_item_new ();
  gtk_widget_show (s__parateur1);
  gtk_container_add (GTK_CONTAINER (menuitem_help_menu), s__parateur1);
  gtk_widget_set_sensitive (s__parateur1, FALSE);

  about = gtk_menu_item_new_with_mnemonic (_("\303\200 _propos de KF-Ray"));
  gtk_widget_show (about);
  gtk_container_add (GTK_CONTAINER (menuitem_help_menu), about);

  frame_scene = gtk_frame_new (NULL);
  gtk_widget_show (frame_scene);
  gtk_layout_put (GTK_LAYOUT (layout_main), frame_scene, 208, 32);
  gtk_widget_set_size_request (frame_scene, 592, 432);
  gtk_container_set_border_width (GTK_CONTAINER (frame_scene), 4);
  gtk_frame_set_shadow_type (GTK_FRAME (frame_scene), GTK_SHADOW_NONE);

  alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (frame_scene), alignment2);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment2), 0, 0, 12, 0);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_container_add (GTK_CONTAINER (alignment2), scrolledwindow2);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

  viewport_scene = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport_scene);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport_scene);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow3);
  gtk_container_add (GTK_CONTAINER (viewport_scene), scrolledwindow3);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow3), GTK_SHADOW_IN);

  textview_scene = gtk_text_view_new ();
  gtk_widget_show (textview_scene);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), textview_scene);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview_scene), FALSE);

  lbl_frame = gtk_label_new (_("<b>Sc\303\250ne 3D</b>"));
  gtk_widget_show (lbl_frame);
  gtk_frame_set_label_widget (GTK_FRAME (frame_scene), lbl_frame);
  gtk_label_set_use_markup (GTK_LABEL (lbl_frame), TRUE);

  entry_open = gtk_entry_new ();
  gtk_widget_show (entry_open);
  gtk_layout_put (GTK_LAYOUT (layout_main), entry_open, 40, 160);
  gtk_widget_set_size_request (entry_open, 158, 25);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry_open), 8226);

  lbl_open = gtk_label_new (_("Fichier de description :"));
  gtk_widget_show (lbl_open);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_open, 0, 144);
  gtk_widget_set_size_request (lbl_open, 168, 16);

  cmd_open = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_show (cmd_open);
  gtk_layout_put (GTK_LAYOUT (layout_main), cmd_open, 40, 192);
  gtk_widget_set_size_request (cmd_open, 112, 24);

  lbl_img_name = gtk_label_new (_("Sortie Image :"));
  gtk_widget_show (lbl_img_name);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_img_name, 0, 232);
  gtk_widget_set_size_request (lbl_img_name, 120, 16);

  entry_img_name = gtk_entry_new ();
  gtk_widget_show (entry_img_name);
  gtk_layout_put (GTK_LAYOUT (layout_main), entry_img_name, 40, 256);
  gtk_widget_set_size_request (entry_img_name, 158, 24);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry_img_name), 9679);

  cmd_start = gtk_button_new_with_mnemonic (_("Start !"));
  gtk_widget_show (cmd_start);
  gtk_layout_put (GTK_LAYOUT (layout_main), cmd_start, 120, 432);
  gtk_widget_set_size_request (cmd_start, 96, 32);

  chk_parallel = gtk_check_button_new_with_mnemonic (_("Activ\303\251"));
  gtk_widget_show (chk_parallel);
  gtk_layout_put (GTK_LAYOUT (layout_main), chk_parallel, 120, 296);
  gtk_widget_set_size_request (chk_parallel, 72, 16);

  entry_parallel = gtk_entry_new ();
  gtk_widget_show (entry_parallel);
  gtk_layout_put (GTK_LAYOUT (layout_main), entry_parallel, 120, 320);
  gtk_widget_set_size_request (entry_parallel, 56, 24);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry_parallel), 8226);

  lbl_proc = gtk_label_new (_("Processus"));
  gtk_widget_show (lbl_proc);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_proc, 40, 320);
  gtk_widget_set_size_request (lbl_proc, 72, 24);

  lbl_parallel = gtk_label_new (_("Parall\303\251lisation"));
  gtk_widget_show (lbl_parallel);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_parallel, 6, 296);
  gtk_widget_set_size_request (lbl_parallel, 112, 16);

  textview_print = gtk_text_view_new ();
  gtk_widget_show (textview_print);
  gtk_layout_put (GTK_LAYOUT (layout_main), textview_print, 0, 472);
  gtk_widget_set_size_request (textview_print, 800, 128);
  GTK_WIDGET_UNSET_FLAGS (textview_print, GTK_CAN_FOCUS);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview_print), FALSE);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview_print), 4);
  gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textview_print), 4);
  gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview_print)), _("Bienvenue sur KF-Ray GUI l'interface graphique de KF-Ray.\nCeci est la fen\303\252tre d'ex\303\251cution qui affiche des informations lors du rendu.\nTous les champs sont optionnels vous pouvez simplement appuyer directement sur Start !"), -1);

  lbl_generate = gtk_label_new (_("G\303\251n\303\251rateur"));
  gtk_widget_show (lbl_generate);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_generate, 6, 360);
  gtk_widget_set_size_request (lbl_generate, 88, 24);

  chk_generate = gtk_check_button_new_with_mnemonic (_("Activ\303\251"));
  gtk_widget_show (chk_generate);
  gtk_layout_put (GTK_LAYOUT (layout_main), chk_generate, 120, 368);
  gtk_widget_set_size_request (chk_generate, 72, 16);

  entry_sample = gtk_entry_new ();
  gtk_widget_show (entry_sample);
  gtk_layout_put (GTK_LAYOUT (layout_main), entry_sample, 120, 392);
  gtk_widget_set_size_request (entry_sample, 56, 24);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry_sample), 9679);

  lbl_samples = gtk_label_new (_("Echantillons"));
  gtk_widget_show (lbl_samples);
  gtk_layout_put (GTK_LAYOUT (layout_main), lbl_samples, 32, 393);
  gtk_widget_set_size_request (lbl_samples, 78, 20);

  img_logo = create_pixmap (win_main, "logo.jpg");
  gtk_widget_show (img_logo);
  gtk_layout_put (GTK_LAYOUT (layout_main), img_logo, 0, 24);
  gtk_widget_set_size_request (img_logo, 160, 80);

  g_signal_connect ((gpointer) open, "activate",
                    G_CALLBACK (on_open_activate),
                    NULL);
  g_signal_connect ((gpointer) clean_img, "activate",
                    G_CALLBACK (on_clean_img_activate),
                    NULL);
  g_signal_connect ((gpointer) quitter, "activate",
                    G_CALLBACK (on_quit_activate),
                    NULL);
  g_signal_connect ((gpointer) simple, "activate",
                    G_CALLBACK (on_simple_light_activate),
                    NULL);
  g_signal_connect ((gpointer) lambert, "activate",
                    G_CALLBACK (on_lambert_activate),
                    NULL);
  g_signal_connect ((gpointer) phong, "activate",
                    G_CALLBACK (on_phong_activate),
                    NULL);
  g_signal_connect ((gpointer) blinn_phong, "activate",
                    G_CALLBACK (on_blinnphong_activate),
                    NULL);
  g_signal_connect ((gpointer) perlin, "activate",
                    G_CALLBACK (on_perlin_activate),
                    NULL);
  g_signal_connect ((gpointer) antialiasing, "activate",
                    G_CALLBACK (on_antialiasing_activate),
                    NULL);
  g_signal_connect ((gpointer) log, "activate",
                    G_CALLBACK (on_log_activate),
                    NULL);
  g_signal_connect ((gpointer) copying, "activate",
                    G_CALLBACK (on_copying_activate),
                    NULL);
  g_signal_connect ((gpointer) about, "activate",
                    G_CALLBACK (on_about_activate),
                    NULL);
  g_signal_connect ((gpointer) cmd_open, "clicked",
                    G_CALLBACK (on_cmd_open_clicked),
                    NULL);
  g_signal_connect ((gpointer) cmd_start, "clicked",
                    G_CALLBACK (on_cmd_start_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (win_main, win_main, "win_main");
  GLADE_HOOKUP_OBJECT (win_main, alignment_main, "alignment_main");
  GLADE_HOOKUP_OBJECT (win_main, scrolledwindow_main, "scrolledwindow_main");
  GLADE_HOOKUP_OBJECT (win_main, layout_main, "layout_main");
  GLADE_HOOKUP_OBJECT (win_main, _filemenu_main, "_filemenu_main");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_file, "menuitem_file");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_file_menu, "menuitem_file_menu");
  GLADE_HOOKUP_OBJECT (win_main, open, "open");
  GLADE_HOOKUP_OBJECT (win_main, clean_img, "clean_img");
  GLADE_HOOKUP_OBJECT (win_main, separatormenuitem1, "separatormenuitem1");
  GLADE_HOOKUP_OBJECT (win_main, quitter, "quitter");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_eclairage, "menuitem_eclairage");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_eclairage_menu, "menuitem_eclairage_menu");
  GLADE_HOOKUP_OBJECT (win_main, simple, "simple");
  GLADE_HOOKUP_OBJECT (win_main, lambert, "lambert");
  GLADE_HOOKUP_OBJECT (win_main, phong, "phong");
  GLADE_HOOKUP_OBJECT (win_main, blinn_phong, "blinn_phong");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_texture, "menuitem_texture");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_texture_menu, "menuitem_texture_menu");
  GLADE_HOOKUP_OBJECT (win_main, perlin, "perlin");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_options, "menuitem_options");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_options_menu, "menuitem_options_menu");
  GLADE_HOOKUP_OBJECT (win_main, antialiasing, "antialiasing");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_help, "menuitem_help");
  GLADE_HOOKUP_OBJECT (win_main, menuitem_help_menu, "menuitem_help_menu");
  GLADE_HOOKUP_OBJECT (win_main, log, "log");
  GLADE_HOOKUP_OBJECT (win_main, copying, "copying");
  GLADE_HOOKUP_OBJECT (win_main, s__parateur1, "s__parateur1");
  GLADE_HOOKUP_OBJECT (win_main, about, "about");
  GLADE_HOOKUP_OBJECT (win_main, frame_scene, "frame_scene");
  GLADE_HOOKUP_OBJECT (win_main, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (win_main, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT (win_main, viewport_scene, "viewport_scene");
  GLADE_HOOKUP_OBJECT (win_main, scrolledwindow3, "scrolledwindow3");
  GLADE_HOOKUP_OBJECT (win_main, textview_scene, "textview_scene");
  GLADE_HOOKUP_OBJECT (win_main, lbl_frame, "lbl_frame");
  GLADE_HOOKUP_OBJECT (win_main, entry_open, "entry_open");
  GLADE_HOOKUP_OBJECT (win_main, lbl_open, "lbl_open");
  GLADE_HOOKUP_OBJECT (win_main, cmd_open, "cmd_open");
  GLADE_HOOKUP_OBJECT (win_main, lbl_img_name, "lbl_img_name");
  GLADE_HOOKUP_OBJECT (win_main, entry_img_name, "entry_img_name");
  GLADE_HOOKUP_OBJECT (win_main, cmd_start, "cmd_start");
  GLADE_HOOKUP_OBJECT (win_main, chk_parallel, "chk_parallel");
  GLADE_HOOKUP_OBJECT (win_main, entry_parallel, "entry_parallel");
  GLADE_HOOKUP_OBJECT (win_main, lbl_proc, "lbl_proc");
  GLADE_HOOKUP_OBJECT (win_main, lbl_parallel, "lbl_parallel");
  GLADE_HOOKUP_OBJECT (win_main, textview_print, "textview_print");
  GLADE_HOOKUP_OBJECT (win_main, lbl_generate, "lbl_generate");
  GLADE_HOOKUP_OBJECT (win_main, chk_generate, "chk_generate");
  GLADE_HOOKUP_OBJECT (win_main, entry_sample, "entry_sample");
  GLADE_HOOKUP_OBJECT (win_main, lbl_samples, "lbl_samples");
  GLADE_HOOKUP_OBJECT (win_main, img_logo, "img_logo");

  gtk_window_add_accel_group (GTK_WINDOW (win_main), accel_group);

  return win_main;
}
