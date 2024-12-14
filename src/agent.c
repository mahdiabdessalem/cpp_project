#include "agent.h" 
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

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
    if (strlen(cin) != 8 )return 0;
    for (int i = 0; i < 8; i++) {
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
    fprintf(f, "%s %s %s %s %s %s %s %s %s  %d %d %d %d %d %d %d \n", a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,a.region, a.ville, a.role_agent, a.parking_assigne, a.statut,a.dn.jour, a.dn.mois, a.dn.annee,a.db.jour, a.db.mois, a.db.annee);

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
    GtkListStore *store;store = gtk_list_store_new(10, 
        G_TYPE_STRING, // Nom
        G_TYPE_STRING, // Prenom
        G_TYPE_STRING, // CIN
        G_TYPE_STRING, // Email
        G_TYPE_STRING, // Telephone
        G_TYPE_INT,    // Statut
        G_TYPE_INT,    // DN: Jour
        G_TYPE_INT,    // DN: Mois
        G_TYPE_INT,    // DN: Annee
        G_TYPE_STRING  // Role
    );

    // Attach the model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
// Debugging check to see if the model is set correctly
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (!model) {
        g_warning("TreeView model is not set!");
    } else {
        g_print("TreeView model is set.\n");
    }
    g_object_unref(store); // Reduce ref count for the store

    // Add columns for each field
    renderer = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Telephone", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Statut", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("DN: Jour", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("DN: Mois", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("DN: Annee", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Role", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}
void load_agents_into_treeview(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;

    FILE *file = fopen("agents.txt", "r");
    if (!file) {
        g_warning("Could not open agents.txt");
        return;
    } else {
        g_print("File opened successfully\n");  // Debugging message
    }

    agent a;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    int read_count; // To track how many fields fscanf reads
    char line[1024];  // Buffer to read lines (adjust size if needed)

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\0' || line[0] == '\n') {
            continue;
        }

        // Use sscanf instead of fscanf to read from the buffer line
        read_count = sscanf(line, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d",
            a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, 
            a.parking_assigne, a.ville, a.region, a.role_agent,
            &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee, 
            &a.db.jour, &a.db.mois, &a.db.annee);

        // Debugging output: Print each field as sscanf reads it
        g_print("Read %d fields: %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d\n",
            read_count, a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, 
            a.parking_assigne, a.ville, a.region, a.statut, a.dn.jour, a.dn.mois, a.dn.annee, 
            a.db.jour, a.db.mois, a.db.annee, a.role_agent);

        // If exactly 16 fields are read, append them to the list store
        if (read_count == 16) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, a.nom,
                1, a.prenom,
                2, a.cin,
                3, a.mail_dagent,
                4, a.num_telefone,
                5, a.statut,
                6, a.dn.jour,
                7, a.dn.mois,
                8, a.dn.annee,
                9, a.role_agent,
                -1);
        } else {
            g_warning("Failed to read 16 fields from line, only read %d", read_count);
        }
    }

    fclose(file);
}

/*void load_agents_into_treeview(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;

    FILE *file = fopen("agents.txt", "r");
    if (!file) {
        g_warning("Could not open agents.txt");
        return;
    } else {
        g_print("File opened successfully\n");  // Debugging message
    }


    agent a;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
int read_count; // To track how many fields fscanf reads
while ((read_count = fscanf(file, "%s %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d", 
        a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, 
        a.parking_assigne, a.ville, a.region, a.role_agent,
        &a.statut, &a.dn.jour, &a.dn.mois, &a.dn.annee, 
        &a.db.jour, &a.db.mois, &a.db.annee)) != EOF) {

    // Debugging output: Print each field as fscanf reads it
    g_print("Read %d fields: %s %s %s %s %s %s %s %s %d %d %d %d %d %d %d\n",
        read_count, a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, 
        a.parking_assigne, a.ville, a.region, a.statut, a.dn.jour, a.dn.mois, a.dn.annee, 
        a.db.jour, a.db.mois, a.db.annee, a.role_agent);

    // If exactly 16 fields are read, append them to the list store
    if (read_count == 16) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, a.nom,
            1, a.prenom,
            2, a.cin,
            3, a.mail_dagent,
            4, a.num_telefone,
            5, a.statut,
            6, a.dn.jour,
            7, a.dn.mois,
            8, a.dn.annee,
            9, a.role_agent,
            -1);
    } else {
        g_warning("Failed to read 16 fields from line, only read %d", read_count);
    }
}

fclose(file); }*/

   /* while (fscanf(file, "%s %s %s %s %s %d %d %d %d %d %d %d %d %s", 
        a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone, &a.statut, 
        &a.dn.jour, &a.dn.mois, &a.dn.annee,  &a.db.jour,&a.db.mois,&a.db.annee,
        a.role_agent) == 13) {
/// Debugging output to see what is being read from the file
        g_print("Read: %s %s %s %s %s %d %d %d %d %d %d %d %d %s\n", 
                a.nom, a.prenom, a.cin, a.mail_dagent, a.num_telefone,
                a.statut, a.dn.jour, a.dn.mois, a.dn.annee, 
                a.db.jour, a.db.mois, a.db.annee, a.role_agent);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
 
            0, a.nom,
            1, a.prenom,
            2, a.cin,
            3, a.mail_dagent,
            4, a.num_telefone,
            5, a.statut,
            6, a.dn.jour,
            7, a.dn.mois,
            8, a.dn.annee,
            9, a.role_agent,
            -1);
    }
// Check if fscanf didn't read all fields as expected
    if (read_count != 13) {
        g_warning("Warning: fscanf read %d fields instead of 13", read_count);
    }
    fclose(file);
}
*/
///afficher 
void on_window_show(GtkWidget *widget, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(widget, "treeview_agents");

    setup_treeview(treeview);   // Initialize the TreeView
    load_agents_into_treeview(treeview); // Load data from file
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








