#include <gtk/gtk.h>


void
on_buttonajout_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonchercher_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonenregistrer_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_agents_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_chercher_aff_clicked         (GtkButton       *button,
                                        gpointer         user_data);
