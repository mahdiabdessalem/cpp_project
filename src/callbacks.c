#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "agent.h"
#include <glib.h>  

void
on_buttonajout_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *nom, *prenom, *cin, *mail, *telephone,*dn,*db,*label55;

    GtkWidget *jr, *m, *an,*jr1, *m1, *an1;;
    GtkWidget *role, *parking, *ville, *region;
    GtkWidget *actif, *inactif,*statut;
GtkWidget *entry_nom, *entry_prenom, *entry_cin,*entry_mail,*entry_telephone;
    GtkWidget *entry_role, *entry_parking, *entry_ville, *entry_region;
    


    char filename[]="agents.txt";
    agent a;

// Lookup Entry widgets with debug statements
    nom = lookup_widget(GTK_WIDGET(button), "entry_nom");
    if (!nom) {
        g_warning("entry_nom not found!");
    }

    prenom = lookup_widget(GTK_WIDGET(button), "entry_prenom");
    if (!prenom) {
        g_warning("entry_prenom not found!");
    }

    cin = lookup_widget(GTK_WIDGET(button), "entry_cin");
    if (!cin) {
        g_warning("entry_cin not found!");
    }

    mail = lookup_widget(GTK_WIDGET(button), "entry_mail");
    if (!mail) {
        g_warning("entry_mail not found!");
    }

    telephone = lookup_widget(GTK_WIDGET(button), "entry_telephone");
    if (!telephone) {
        g_warning("entry_telephone not found!");
    }

    db = lookup_widget(GTK_WIDGET(button), "db");
    if (!db) {
        g_warning("db SpinButton not found!");
    }

    dn = lookup_widget(GTK_WIDGET(button), "dn");
    if (!dn) {
        g_warning("dn SpinButton not found!");
    }

    jr = lookup_widget(GTK_WIDGET(button), "jr");
    if (!jr) {
        g_warning("jr SpinButton not found!");
    }

    m = lookup_widget(GTK_WIDGET(button), "m");
    if (!m) {
        g_warning("m SpinButton not found!");
    }

    an = lookup_widget(GTK_WIDGET(button), "an");
    if (!an) {
        g_warning("an SpinButton not found!");
    }

    jr1 = lookup_widget(GTK_WIDGET(button), "jr1");
    if (!jr1) {
        g_warning("jr1 SpinButton not found!");
    }

    m1 = lookup_widget(GTK_WIDGET(button), "m1");
    if (!m1) {
        g_warning("m1 SpinButton not found!");
    }

    an1 = lookup_widget(GTK_WIDGET(button), "an1");
    if (!an1) {
        g_warning("an1 SpinButton not found!");
    }

    // Lookup ComboBox widgets with debug statements
    role = lookup_widget(GTK_WIDGET(button), "entry_role");
    if (!role) {
        g_warning("entry_role ComboBox not found!");
    }

    parking = lookup_widget(GTK_WIDGET(button), "entry_parking");
    if (!parking) {
        g_warning("entry_parking ComboBox not found!");
    }

    ville = lookup_widget(GTK_WIDGET(button), "entry_ville");
    if (!ville) {
        g_warning("entry_ville ComboBox not found!");
    }

    region = lookup_widget(GTK_WIDGET(button), "entry_region");
    if (!region) {
        g_warning("entry_region ComboBox not found!");
    }

    statut = lookup_widget(GTK_WIDGET(button), "statut");
    if (!statut) {
        g_warning("statut CheckButton not found!");
    }

    actif = lookup_widget(GTK_WIDGET(button), "actif");
    if (!actif) {
        g_warning("actif ToggleButton not found!");
    }

    inactif = lookup_widget(GTK_WIDGET(button), "inactif");
    if (!inactif) {
        g_warning("inactif ToggleButton not found!");
    }

    label55 = lookup_widget(GTK_WIDGET(button), "label55");
    if (!label55) {
        g_warning("label55 not found!");
    }

    // Once you've confirmed that the widgets are found, proceed to get text
    if (nom && prenom && cin && mail && telephone && role && parking && ville && region) {
        strcpy(a.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
        strcpy(a.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
        strcpy(a.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
        strcpy(a.mail_dagent, gtk_entry_get_text(GTK_ENTRY(mail)));
        strcpy(a.num_telefone, gtk_entry_get_text(GTK_ENTRY(telephone)));

        strcpy(a.role_agent, gtk_combo_box_get_active_text(GTK_COMBO_BOX(role)));
        strcpy(a.parking_assigne, gtk_combo_box_get_active_text(GTK_COMBO_BOX(parking)));
        strcpy(a.ville, gtk_combo_box_get_active_text(GTK_COMBO_BOX(ville)));
        strcpy(a.region, gtk_combo_box_get_active_text(GTK_COMBO_BOX(region)));

        // Continue with SpinButton values and toggle state as needed...
        a.dn.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jr));
        a.dn.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
        a.dn.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(an));

        a.db.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jr1));
        a.db.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m1));
        a.db.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(an1));

        // Set statut based on toggle buttons...
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(actif))) {
            a.statut = 1;
        } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inactif))) {
            a.statut = 0;
        }
    } else {
        g_warning("One or more widget lookups failed.");
        return;
    }

  
    int result = ajouter("agents.txt", a);
    // Check the result and update the label with a message
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label55), "Agent ajouté avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(label55), "Erreur lors de l'ajout de l'agent.");
    }

}

void
on_button_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *notebook = lookup_widget(GTK_WIDGET(button), "notebook1"); // Replace "notebook" with the actual widget name of your notebook
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview_agents"); // Replace "treeview_agents" with the actual widget name of your TreeView

    // Switch to the second page (page index starts at 0)
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1);

    // Setup TreeView and load data
    setup_treeview(treeview); // Initialize TreeView columns
    load_agents_into_treeview(treeview); // Populate TreeView with data from the file

}
/////////////bouton chercher selon cin pour laffichage
void
on_button_chercher_aff_clicked         (GtkButton       *button,
                                        gpointer         user_data){
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview_agents");
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry_cin"); // The CIN entry widget
    const char *cin_filter = gtk_entry_get_text(GTK_ENTRY(entry_cin)); // Get the CIN text from the entry

    if (cin_filter && cin_filter[0] != '\0') {
        filter_treeview_by_cin(treeview, cin_filter);
    } else {
        // If no CIN is provided, you can reload all the agents
        load_agents_into_treeview(treeview); // Reload the TreeView with all agents
    }
}
void on_treeview_agents_row_activated(
    GtkTreeView *treeview,
    GtkTreePath *path,
    GtkTreeViewColumn *column,
    gpointer user_data) 
{
    // Get the selected row from the treeview
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    gchar *nom, *prenom, *cin, *email;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Fetch the values from the row at the selected path
        gtk_tree_model_get(model, &iter,
            0, &nom,  // Get "Nom" (index 0)
            1, &prenom,  // Get "Prenom" (index 1)
            2, &cin,  // Get "CIN" (index 2)
            3, &email,  // Get "Email" (index 3)
            -1);

        // Do something with the values, e.g., print them
        g_print("Row activated: %s %s %s %s\n", nom, prenom, cin, email);

        // Free the memory
        g_free(nom);
        g_free(prenom);
        g_free(cin);
        g_free(email);
    }
}




void
on_buttonchercher_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
//Declare Entry widgets (for user input)
    GtkWidget *entry_nom_modif, *entry_prenom_modif, *entry_cin_modif, *entry_cin1_modif, *entry_mail_modif, *entry_telephone_modif;
    GtkWidget *entry_role_modif, *entry_parking_modif, *entry_ville_modif, *entry_region_modif;
    GtkWidget *jr_modif, *m_modif, *an_modif, *jr1_modif, *m1_modif, *an1_modif;
    GtkWidget *actif_modif, *inactif_modif,*error_modif;

    // Declare Label widgets (for static text beside the entries or error messages)
    
    GtkWidget *nom_modif, *prenom_modif, *cin_modif, *cin1_modif, *mail_modif, *telephone_modif, *dn_modif, *db_modif;
    GtkWidget *role_modif, *parking_modif, *ville_modif, *region_modif, *statut_modif;
    
    // Lookup Entry widget to get the CIN entered by user
    entry_cin1_modif = lookup_widget(GTK_WIDGET(button), "entry_cin1_modif");
    const char *cin = gtk_entry_get_text(GTK_ENTRY(entry_cin1_modif));  // Get CIN entered by user

    // Lookup Label widget for error message display
    error_modif = lookup_widget(GTK_WIDGET(button), "error_modif");

    // Call the cher function to search for the agent by CIN
    agent a = cher("agents.txt", cin);

    // If agent is found, populate the entry fields
    if (strcmp(a.cin, "Not found") != 0) {
        // Lookup Entry widgets and populate them with agent data
        entry_nom_modif = lookup_widget(GTK_WIDGET(button), "entry_nom_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_nom_modif), a.nom);

        entry_prenom_modif = lookup_widget(GTK_WIDGET(button), "entry_prenom_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_prenom_modif), a.prenom);

        entry_mail_modif = lookup_widget(GTK_WIDGET(button), "entry_mail_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_mail_modif), a.mail_dagent);

        entry_telephone_modif = lookup_widget(GTK_WIDGET(button), "entry_telephone_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_telephone_modif), a.num_telefone);

        entry_role_modif = lookup_widget(GTK_WIDGET(button), "entry_role_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_role_modif), a.role_agent);

        entry_parking_modif = lookup_widget(GTK_WIDGET(button), "entry_parking_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_parking_modif), a.parking_assigne);

        entry_ville_modif = lookup_widget(GTK_WIDGET(button), "entry_ville_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_ville_modif), a.ville);

        entry_region_modif = lookup_widget(GTK_WIDGET(button), "entry_region_modif");
        gtk_entry_set_text(GTK_ENTRY(entry_region_modif), a.region);

        // Populate Date of Birth (use spin buttons for day, month, year)
        jr_modif = lookup_widget(GTK_WIDGET(button), "jr_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jr_modif), a.dn.jour);

        m_modif = lookup_widget(GTK_WIDGET(button), "m_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_modif), a.dn.mois);

        an_modif = lookup_widget(GTK_WIDGET(button), "an_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(an_modif), a.dn.annee);

        jr1_modif = lookup_widget(GTK_WIDGET(button), "jr1_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jr1_modif), a.db.jour);

        m1_modif = lookup_widget(GTK_WIDGET(button), "m1_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(m1_modif), a.db.mois);

        an1_modif = lookup_widget(GTK_WIDGET(button), "an1_modif");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(an1_modif), a.db.annee);

        // Populate Statut (active or inactive)
        statut_modif = lookup_widget(GTK_WIDGET(button), "statut_modif");
        if (a.statut == 1) {
            actif_modif = lookup_widget(GTK_WIDGET(button), "actif_modif");
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(actif_modif), TRUE);
        } else {
            inactif_modif = lookup_widget(GTK_WIDGET(button), "inactif_modif");
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(inactif_modif), TRUE);
        }

        // Clear error message if agent is found
        gtk_label_set_text(GTK_LABEL(error_modif), "");

    } else {
        // If agent is not found, show an error message in the label
        gtk_label_set_text(GTK_LABEL(error_modif), "Agent not found.");
    }
}





void
on_buttonenregistrer_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *entry_nom_modif, *entry_prenom_modif, *entry_cin_modif,*entry_cin1_modif,*entry_mail_modif,*entry_telephone_modif,
*entry_dn_modif,
*entry_db_modif,*label_error_modif;
    GtkWidget *entry_role_modif, *entry_parking_modif, *entry_ville_modif, *entry_region_modif;
    GtkWidget *jr_modif, *m_modif, *an_modif,*jr1_modif, *m1_modif, *an1_modif;
    GtkWidget *actif_modif, *inactif_modif;
//they say
 entry_nom_modif = lookup_widget(GTK_WIDGET(button), "entry_nom_modif");
    entry_prenom_modif = lookup_widget(GTK_WIDGET(button), "entry_prenom_modif");
    entry_cin_modif = lookup_widget(GTK_WIDGET(button), "entry_cin_modif");
    entry_mail_modif = lookup_widget(GTK_WIDGET(button), "entry_mail_modif");
    entry_telephone_modif = lookup_widget(GTK_WIDGET(button), "entry_telephone_modif");
    entry_role_modif = lookup_widget(GTK_WIDGET(button), "entry_role_modif");
    entry_parking_modif = lookup_widget(GTK_WIDGET(button), "entry_parking_modif");
    entry_ville_modif = lookup_widget(GTK_WIDGET(button), "entry_ville_modif");
    entry_region_modif = lookup_widget(GTK_WIDGET(button), "entry_region_modif");
    
    // Lookup Spin Button widgets for the dates
    jr_modif = lookup_widget(GTK_WIDGET(button), "jr_modif");
    m_modif = lookup_widget(GTK_WIDGET(button), "m_modif");
    an_modif = lookup_widget(GTK_WIDGET(button), "an_modif");
    jr1_modif = lookup_widget(GTK_WIDGET(button), "jr1_modif");
    m1_modif = lookup_widget(GTK_WIDGET(button), "m1_modif");
    an1_modif = lookup_widget(GTK_WIDGET(button), "an1_modif");

    // Lookup Toggle Buttons for Statut (Active/Inactive)
    actif_modif = lookup_widget(GTK_WIDGET(button), "actif_modif");
    inactif_modif = lookup_widget(GTK_WIDGET(button), "inactif_modif");

    // Get the CIN value to search for the agent
    const char *cin = gtk_entry_get_text(GTK_ENTRY(entry_cin_modif));

    // Get the new values from the entries
    agent nouv;
    strcpy(nouv.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom_modif)));
    strcpy(nouv.prenom, gtk_entry_get_text(GTK_ENTRY(entry_prenom_modif)));
    strcpy(nouv.cin, cin);  // CIN should stay the same, we just use it to search for the agent
    strcpy(nouv.mail_dagent, gtk_entry_get_text(GTK_ENTRY(entry_mail_modif)));
    strcpy(nouv.num_telefone, gtk_entry_get_text(GTK_ENTRY(entry_telephone_modif)));
    strcpy(nouv.role_agent, gtk_entry_get_text(GTK_ENTRY(entry_role_modif)));
    strcpy(nouv.parking_assigne, gtk_entry_get_text(GTK_ENTRY(entry_parking_modif)));
    strcpy(nouv.ville, gtk_entry_get_text(GTK_ENTRY(entry_ville_modif)));
    strcpy(nouv.region, gtk_entry_get_text(GTK_ENTRY(entry_region_modif)));

    // Get Date values
    nouv.dn.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jr_modif));
    nouv.dn.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m_modif));
    nouv.dn.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(an_modif));
    nouv.db.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jr1_modif));
    nouv.db.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m1_modif));
    nouv.db.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(an1_modif));

    // Get Statut (Active or Inactive)
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(actif_modif))) {
        nouv.statut = 1;  // Active
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inactif_modif))) {
        nouv.statut = 0;  // Inactive
    }

    // Call the modifier function to save the changes to the file
    int result = modifier("agents.txt", cin, nouv);

   label_error_modif = lookup_widget(GTK_WIDGET(button), "label_error_modif");
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label_error_modif), "Agent modified successfully!");
    } else {
        gtk_label_set_text(GTK_LABEL(label_error_modif), "Error modifying the agent."); }}









