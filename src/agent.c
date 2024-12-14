#include "agent.h" 
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ctype.h> // Add this line

const char *regions_urbaines[] = {
    "Tunis", "Sousse", "Sfax", "Ariana", "Bizerte", "Mannouba", "Nabeul", 
    "Kairouan", "Gabès", "Sidi Bouzid", "Mahdia", "Tozeur", "Kasserine", 
    "Jendouba", "Medenine"
};


const char *villes_tunis[] = {"Tunis", "La Marsa", "Carthage", "El Menzah", "Sidi Bou Saïd", "Ariana"};
const char *villes_sousse[] = {"Sousse", "Port El Kantaoui", "Kalaa Kebira", "Sidi Bou Ali"};
const char *villes_sfax[] = {"Sfax", "Menzel Chaker", "Gremda"};
const char *villes_arianna[] = {"Ariana", "Raoued", "Ksar Hellal"};
const char *villes_bizerte[] = {"Bizerte", "Menzel Bourguiba", "Mateur"};
const char *villes_mannouba[] = {"Douar Hicher", "El Intilaka", "La Manouba"};
const char *villes_nabeul[] = {"Nabeul", "Hammamet", "Kélibia"};
const char *villes_kairouan[] = {"Kairouan", "El Ala", "Haffouz"};
const char *villes_gabes[] = {"Gabès", "Mareth", "Tataouine"};
const char *villes_sidi_bouzid[] = {"Sidi Bouzid", "Meknassy", "Sidi Ali Ben Aoun"};
const char *villes_mahdia[] = {"Mahdia", "Chebba", "Boumerdes"};
const char *villes_tozeur[] = {"Tozeur", "Nefta", "Degache"};
const char *villes_kasserine[] = {"Kasserine", "Sbeïtla", "Thala"};
const char *villes_jendouba[] = {"Jendouba", "Bousalem", "Oued Meliz"};
const char *villes_medenine[] = {"Medenine", "Ben Gardane", "Zarzis"};


const char *roles_agent[] = {"Agent de nettoyage","Agent de sécurité", "Agent d'accueil","Agent de surveillance", "Responsable Parking", "Superviseur"};


const char *parkings_assignes[] = {"Parking 1", "Parking 2", "Parking 3", "Parking 4", "Parking 5"};

 
int verifier_date(date d) {
    if (d.jour < 1 || d.jour > 31) return 0;  // Invalid day
    if (d.mois < 1 || d.mois > 12) return 0;  // Invalid month
    if (d.annee < 1900 || d.annee > 2100) return 0;  // Arbitrary year range
    return 1;  // Valid date
}

int verifier_cin(const char *cin) {
    for (int i = 0; cin[i] != '\0'; i++) {
        if (!isdigit(cin[i])) return 0;
    }
    return 1;
}

int verifier_telephone(const char *telephone) {
    if (strlen(telephone) < 8 || strlen(telephone) > 15) return 0;
    for (int i = 0; telephone[i] != '\0'; i++) {
        if (!isdigit(telephone[i])) return 0;
    }
    return 1;
}

int verifier_email(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return (at && dot && at < dot);  
}

//AJOUT
int ajouter(char *filename, agent a)
 {
    FILE *f = fopen(filename, "a");
    if (f != NULL)
  { 
    fprintf(f, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d\n", 
            a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
            a.region, a.ville, a.role_agent, a.parking_assigne, 
            a.statut, a.dn.jour, a.dn.mois, a.dn.annee,
            a.db.jour, a.db.mois, a.db.annee);

      fclose(f);
    return 1;
   }
else return 0 ;
}

//modif
int modifier(char *filename, char *cin, agent nouv) {
    int tr = 0;
    agent a;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, " %s %s %s %s %s %s %s %s %s  %d %d%d%d %d %d %d \n",
 a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
 a.region, a.ville, a.role_agent, a.parking_assigne, &a.statut,
 &a.dn.jour, &a.dn.mois, &a.dn.annee,
 &a.db.jour, &a.db.mois, &a.db.annee) != EOF) {
            if (strcmp(a.cin,cin)==0) { 
                fprintf(f2, "%s %s %s %s %s %s %s %s %s  %d %d%d%d %d %d %d \n",
nouv.nom, nouv.prenom, nouv.cin, nouv.mail_dagent, nouv.num_telefone, nouv.region, nouv.ville, nouv.role_agent, nouv.parking_assigne, nouv.statut, nouv.dn.jour, nouv.dn.mois, nouv.dn.annee, nouv.db.jour, nouv.db.mois, nouv.db.annee);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %s %s %s %s %s  %d %d%d%d %d %d %d \n",
 a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
 a.region, a.ville, a.role_agent, a.parking_assigne, a.statut,
 a.dn.jour, a.dn.mois, a.dn.annee,
 a.db.jour, a.db.mois, a.db.annee);
            }
        }
        fclose(f);
        fclose(f2);

        if (tr == 1) {
            remove(filename);
            rename("nouv.txt", filename);
        } else {
remove("nouv.txt");
        }
    } else {
        if (f) fclose(f);
        if (f2) fclose(f2);
    }

    return tr;
}
       

//supp
int supprimer(char *filename, char *cin) {
    int tr = 0;
    agent a;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f != NULL && f2 != NULL) 
      {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s  %d %d%d%d %d %d %d\n",
 a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
 a.region, a.ville, a.role_agent, a.parking_assigne, &a.statut,&a.dn.jour, &a.dn.mois, &a.dn.annee,
&a.db.jour, &a.db.mois, &a.db.annee) != EOF) 
            {

            if (strcmp(a.cin,cin)==0) tr=1 ;
           else fprintf(f2, "%s %s %s %s %s %s %s %s %s  %d %d%d%d %d %d %d\n",
 a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
 a.region, a.ville, a.role_agent, a.parking_assigne, a.statut, a.dn.jour, a.dn.mois, a.dn.annee, a.db.jour, a.db.mois, a.db.annee); 
            } 
        }
        fclose(f);
        fclose(f2);
remove(filename);
rename("temp.txt", filename);

        
    return tr;
}
agent cher(const char *filename, const char *cin) {
    agent a = {0};
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d", 
                a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, 
                a.region, a.ville, a.role_agent, a.parking_assigne,
                &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee,
                &a.db.jour, &a.db.mois, &a.db.annee) == 16) {
            if (strcmp(a.cin, cin) == 0) {
                fclose(f);
                return a;
            }
        }
        fclose(f);
    }

    strcpy(a.cin, "Not found");
    return a;
}

/*agent a = {0}; // Initialize all fields to zero or empty
    FILE *f = fopen(filename, "r"); 

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d",
                a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
                a.region, a.ville, a.role_agent, a.parking_assigne,
                &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee,
                &a.db.jour, &a.db.mois, &a.db.annee) == 16) {// Clean up both CIN strings before comparing
           

            printf("Comparing entered CIN: '%s' with file CIN: '%s'\n", cin, a.cin); // Debugging output

            if (strcmp(a.cin, cin) == 0) {
                fclose(f);
                return a; // Agent found, return agent
            }
        }
        fclose(f);
    }
    
    // If no match, return agent with empty or default data
    strcpy(a.cin, "Not found");
    return a;
}*/
/*
//cher
agent cher(const char *filename1, const char *cin) {
    agent a;
    FILE *f1 = fopen(filename1, "r");

    if (f1 == NULL) {
        perror("File open error");
        snprintf(a.cin, sizeof(a.cin), "Not found");
        return a;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), f1) != NULL) {
        sscanf(line, "%s %s %s %s %s %s %s %s %s %d %d%d%d %d %d %d\n",
 a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
 a.region, a.ville, a.role_agent, a.parking_assigne, &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee, &a.db.jour, &a.db.mois, &a.db.annee);
        // Nettoyer les sauts de ligne
        line[strcspn(line, "\n")] = 0;

        // Vérifier les conditions de recherche
        if (strcmp(a.cin,a.cin) == 0 ) {
            found = 1;
            break;
        }
    }
    fclose(f1);

    if (!found) {
        snprintf(a.cin, sizeof(a.cin), "Not found");
    }

    return a;
}*/


//////////////
/*reservation chercher_reserv_par_date(char *filename1, char *filename2, date date_reservation) {
    reservation res;
    reservation res_vide = {"","",{0,0,0},0,0,0};  // Initialize the empty reservation with an invalid ID
strcpy(res_vide.id_reservation, "");

    FILE *f1 = fopen(filename1, "r");
    FILE *f2 = fopen(filename2, "r");

    if (f1 != NULL && f2 != NULL) {
        agent a;
        while (fscanf(f2, "%s %s %d %d %d %d %d %d ",
            &a.rsv.id_reservation, a.rsv.cin,
            &a.rsv.date_reservation.jour, &a.rsv.date_reservation.mois,
            &a.rsv.date_reservation.annee, &a.rsv.heure_debut, &a.rsv.heure_fin, &a.rsv.station_parking) == 10) {
            // Compare reservation date with the provided date
            if (a.rsv.date_reservation.annee == date_reservation.annee &&
                a.rsv.date_reservation.mois == date_reservation.mois &&
                a.rsv.date_reservation.jour == date_reservation.jour) {
                res = a.rsv;  // If a match is found, store the reservation
                fclose(f1);
                fclose(f2);
                return res;  // Return the reservation data
            }
        }
        fclose(f2);
    } else {
        printf("Error: Could not open one or both files for reservation\n");
        if (f1 != NULL) fclose(f1);
        if (f2 != NULL) fclose(f2);
    }

    return res_vide;  // Return an empty reservation if not found
}
*/

/*
agent chercher(char *filename, char *cin) {
    agent a;
    int found = 0; 
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
       
        while (found == 0 && fscanf(f, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d", a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, a.region, a.ville, a.role_agent, a.parking_assigne, &a.statut, &a.date_naissance.jour, &a.date_naissance.mois, &a.date_naissance.annee, &a.date_debut.jour, &a.date_debut.mois, &a.date_debut.annee) == 16) {
            if (strcmp(a.cin, cin) == 0) {
                found = 1; 
            }
        }
        fclose(f);
    }

    if (found == 0) {
        strcpy(a.cin, ""); 
    }

    return a;
}

reservation chercher_reservation_par_date(char *filename, date date_reservation) {
    FILE *file = fopen(filename, "rb");  
    reservation res;
    reservation res_vide = {-1}; 

    if (!file) {
        printf("fichier ne peuet pas etre ouvrir\n");
        return res_vide;
    }

    agent a;
    while (fread(&a, sizeof(agent), 1, file) == 1) {
        
        if (a.rsv.date_reservation.annee == date_reservation.annee &&
            a.rsv.date_reservation.mois == date_reservation.mois &&
            a.rsv.date_reservation.jour == date_reservation.jour) {
            res = a.rsv; 
            fclose(file);
            return res;
        }
    }

    fclose(file);
    return res_vide;  
}

*/
void setup_treeview(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    // Create columns first
    renderer = gtk_cell_renderer_text_new();

    // Define column names and create columns
    const char *column_names[] = {
        "Nom", "Prénom", "CIN", "Email", "Téléphone", 
        "Region", "Ville", "Role", "Parking", "Statut",
        "Jour N.", "Mois N.", "Année N.", 
        "Jour D.", "Mois D.", "Année D."
    };

    // Create store
    store = gtk_list_store_new(16,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  // nom, prenom, cin
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  // email, tel, region
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  // ville, role, parking
        G_TYPE_INT,                                   // statut
        G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,          // date naissance
        G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);         // date debut

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Create all columns with proper attributes
    for (int i = 0; i < 16; i++) {
        column = gtk_tree_view_column_new_with_attributes(
            column_names[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        gtk_tree_view_column_set_resizable(column, TRUE);
        gtk_tree_view_column_set_sortable(column, TRUE);
    }

    g_object_unref(store);
}

void load_agents_into_treeview(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    agent a;
    char line[1024];

    // Get the store
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    gtk_list_store_clear(store);

    FILE *f = fopen("agents.txt", "r");
    if (!f) {
        g_print("Error: Cannot open agents.txt\n");
        return;
    }
    g_print("File opened successfully\n");

    // Skip empty lines and properly parse each line
    while (fgets(line, sizeof(line), f)) {
        // Skip empty lines
        if (strlen(line) <= 1) continue;
        
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // Parse the line with proper format specifiers and error checking
        int read = sscanf(line, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d",
            a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
            a.region, a.ville, a.role_agent, a.parking_assigne,
            &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee,
            &a.db.jour, &a.db.mois, &a.db.annee);

        g_print("Read %d fields: %s\n", read, line);

        if (read == 16) { // Only add if we read all fields successfully
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, a.nom,
                1, a.prenom,
                2, a.cin,
                3, a.mail_dagent,
                4, a.num_telefone,
                5, a.region,
                6, a.ville,
                7, a.role_agent,
                8, a.parking_assigne,
                9, a.statut,
                10, a.dn.jour,
                11, a.dn.mois,
                12, a.dn.annee,
                13, a.db.jour,
                14, a.db.mois,
                15, a.db.annee,
                -1);
        } else {
            g_print("WARNING: Failed to read 16 fields from line, only read %d\n", read);
        }
    }

    fclose(f);

    // Make sure all columns are visible
    GList *columns = gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview));
    for (GList *col = columns; col != NULL; col = col->next) {
        gtk_tree_view_column_set_visible(GTK_TREE_VIEW_COLUMN(col->data), TRUE);
    }
    g_list_free(columns);
}

// Update the filter function to work with the new structure
void filter_treeview_by_cin(GtkWidget *treeview, const char *cin_filter) {
    if (!cin_filter || strlen(cin_filter) == 0) {
        // If no filter, reload all data
        load_agents_into_treeview(treeview);
        return;
    }

    GtkListStore *store;
    GtkTreeIter iter;
    gboolean valid;
    char *cin;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);

    while (valid) {
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 2, &cin, -1);
        
        if (cin != NULL) {
            if (strstr(cin, cin_filter) == NULL) {
                valid = gtk_list_store_remove(store, &iter);
            } else {
                valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
            }
            g_free(cin);
        } else {
            valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
        }
    }
}

void apply_css_styling(GtkWidget *widget) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "treeview {"
        "    font-family: 'Sans';"
        "    font-size: 11px;"
        "}"
        "treeview:selected {"
        "    background-color: #3584e4;"
        "    color: white;"
        "}"
        "treeview header button {"
        "    background-color: #f6f5f4;"
        "    padding: 5px;"
        "    font-weight: bold;"
        "}", -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void on_window_show(GtkWidget *widget, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "your_ui_file.ui", NULL);
    GtkWidget *treeview = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_agents"));

    // Ensure the treeview is set up correctly
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Column Title", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Add your logic to populate the treeview with data from the database
    GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeIter iter;

    // Example data, replace with your database data
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Example Data", -1);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
//////////////Function to filter TreeView based on CIN
void filter_treeview_by_cin(GtkWidget *treeview, const char *cin_filter) {
    GtkListStore *store;
    GtkTreeIter iter;
    gboolean valid_iter;
    
    // Get the list store from the TreeView model
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    // Start at the first row and iterate through each row
    valid_iter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);
    
    while (valid_iter) {
        agent a;
        
        // Get the data for the current row
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
            0, a.nom,
            1, a.prenom,
            2, a.cin,
            3, a.mail_dagent,
            4, a.num_telefone,
            5, &a.statut,
            6, &a.dn.jour,
            7, &a.dn.mois,
            8, &a.dn.annee,
            9, a.role_agent,
            -1);

        // Check if the CIN matches the filter
        if (g_strcmp0(a.cin, cin_filter) != 0) {
            // If it doesn't match, remove the row
            gtk_list_store_remove(store, &iter);
        } else {
            // Move to the next row
            valid_iter = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
        }
    }
}








