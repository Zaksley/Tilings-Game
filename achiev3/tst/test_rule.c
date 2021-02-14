#include <stdio.h>
#include "../src/rule.h"
#include "test_rule.h"
#include "outils.h"

int test_board_init()
{
    printf("  Debut test board_init\n");
    int error = 0;
    int taille = 5;
    int nb_players = 2;
    struct board b = board_init(taille, nb_players);

    if (b.taille == taille) {
        text_green();
        printf("    Taille du board valide\n");

        int erreur = 0;
        int le = -1;
        int ce = -1;
        for (int l = 0; l < b.taille; ++ l) {
            for (int c = 0; c < b.taille; ++ c) {
                if (! tile_equals(empty_tile(), b.plateau[l][c]) || b.from_player[l][c][0] != -1) {
                    erreur ++;
                    le = l;
                    ce = c;
                }                
            }    
        }
        if(erreur == 0) {
          text_green();
          printf("    Le board est bien compose de tuile vide et from_player est bien initialise a -1 partout\n");
        } else {
          error += erreur;
          text_red();
          printf("    ERROR : il y a %d tuiles non vides ou cases de from_player differentes de -1 ex ligne %d, colonne %d, from_player %d\n",
           erreur, le, ce, b.from_player[le][ce][0]);
        }
    } else {
      error ++;
      text_red();
      printf("    Error : Taille du board invalide %d au lieu de %d\n",b.taille,taille);
    }

    return error;
    printf("  Fin test board_init\n");
}

int test_authorized_places()
{
    printf("  Debut test authorized_places\n");
    int error = 0;
    int taille = 3;
    int nb_players = 2;
    struct board b = board_init(taille, nb_players);

    struct deck d;
    deck_init(&d);

    const struct tile * t1 = d.cards[4].t;

    const struct tile * t2 = d.cards[1].t;

    struct position p1 = {.X=1, .Y=1};
    struct position p2 = {.X=0, .Y=2};
    struct position p3 = {.X=2, .Y=0};

    place_tile(&b, t1, p1, 0, nb_players);
    place_tile(&b, t1, p2, 0, nb_players);
    place_tile(&b, t1, p3, 0, nb_players);

    /*

            tuile a place 

                V
              V   V
                V 

            plateau           
            |     |   V  
        NV  | Val | V   R 
            |     |   R 
       ----------------
            |  V  |     
        Val |V   R| NV  
            |  R  |     
       ---------------- 
         V  |     |     
        V R | NV  | NV   
         R  |     |     


    */

    int valides_x[9] = {0};
    int valides_y[9] = {0};

    int x_valides[2] = {0, 1};
    int y_valides[2] = {1, 0};
    int nb_valides = authorized_places(&b, t2, valides_x, valides_y);
    if (nb_valides == 2) {
        text_green();
        printf("    Il y a bien 2 places valides\n");

        int erreur = 0;
        int ie = -1;
        for (int i = 0; i < nb_valides; ++ i) {
            if (! (x_valides[i] == valides_x[i] && y_valides[i] == valides_y[i])) {
                erreur ++;
                ie = i;
            }        
        }
        if(erreur == 0) {
            text_green(); 
            printf("    Les cases valides sont bien aux bonnes positions\n");
        } else {
            error ++;
            text_red();
            printf("    ERROR : il y a %d cases valides aux mauvaises positions ex ligne %d, colonne %d\n", erreur, valides_x[ie], valides_y[ie]);
        }  

    } else {
        error ++;    
        text_red();
        printf("    ERROR : Il y a %d places valides au lieu de 2\n", nb_valides);
    }
   
    text_white();
    printf("  Fin test authorized_places\n");
    return error;
}

int test_position_valide()
{
    printf("  Debut test position_valide\n");
    int error = 0;

    int nb_players = 2;
    int taille = 5;
    struct board b = board_init(taille, nb_players);

    struct deck d;
    deck_init(&d);

    const struct tile * t1 = d.cards[4].t;

    const struct tile * t2 = d.cards[1].t;

    if (! position_valide(&b, t1, 2, 2)) {
      text_green();
      printf("    Une place entouree de case vide est bien invalide\n");    
    } else  {    
      error ++;
      text_red();
      printf("    ERROR : Une place entouree de case vide est considere comme valide\n");    
    }
    struct position p = {.X = 0, .Y = 1};

    place_tile(&b, t2, p, 1, nb_players);

    if (position_valide(&b, t2, 0, 0)) {
      text_green();
      printf("    une case sur les bords est biens valide\n");    
    } else  {    
      error ++;
      text_red();
      printf("    ERROR : une case sur les bords est considere comme invalide\n");    
    }

    p.X = 2;
    p.Y = 2;

    place_tile(&b, t1, p, 1, nb_players);

    if (position_valide(&b, t1, 3, 2)) {
        error ++;
        text_red();
        printf("    ERROR : Deux couleurs differentes au sud et au nord mais la place est considere valide\n");    
    } else  {    
        text_green();
        printf("    Deux couleurs differents donnent bien une place invalide\n");    
    }

    if (position_valide(&b, t2, 1, 2)) {
        text_green();
        printf("    Deux couleurs egales donnent bien une place valide\n");    
    } else  {   
        error ++; 
        text_red();
        printf("    ERROR : Deux couleurs egales au sud et au nord mais la place est considere invalide\n");    
    }
    
    text_white();
    printf("  Fin test position_valide\n");
    return error;
}


int test_place_tile()
{
    printf("  Debut test place_tile\n");
    int error = 0;
    int nb_players = 2;
    int taille = 3;
    struct board b = board_init(taille, nb_players);

    struct deck d;
    deck_init(&d);

    const struct tile * t = d.cards[0].t;

    struct position pos = {.X = 0, .Y = 0};    
    place_tile(&b, t, pos, 0, nb_players);

    if (tile_equals(t, b.plateau[pos.X][pos.Y])) {
        text_green();
        printf("    La tuile a ete bien place\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : la tuile n'a pas été place a la postition %d %d\n", pos.X, pos.Y);
    }

    if (b.from_player[pos.X][pos.Y][0] == 100) {
        text_green();
        printf("    La tuile a ete bien ete place avec une inflence de 100\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : la tuile a ete place avec une influence de %d au lieu de 100\n", b.from_player[pos.X][pos.Y][0]);
    }

    struct position pos_a_place = {.X = 0, .Y = 1};
    place_tile(&b, t, pos_a_place, 1, nb_players);
    if (b.from_player[pos.X][pos.Y][1] == 90) {
        text_green();
        printf("    La tuile a ete bien augmente la tuile a cote de 90\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : la tuile a augmente la tuile a cote de %d au lieu de 90\n", b.from_player[pos.X][pos.Y][1]);
    }

    pos_a_place.X = 1;
    pos_a_place.Y = 0;
    place_tile(&b, t, pos_a_place, 0, nb_players);
    if (b.from_player[pos.X][pos.Y][0] == 180) {
        text_green();
        printf("    La tuile a ete bien augmente la tuile a cote de 80\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : la tuile a augmente la tuile a cote de %d au lieu de 80\n", b.from_player[pos.X][pos.Y][0] - 100);
    }

    text_white();
    printf("  Fin test place_tile\n");
    return error;
}


 int test_select_position()
{
    printf("  Debut test select_position\n");
    int error = 0;
    int nb = 3;
    int Xs[3] = {10, 5, 4};
    int Ys[3] = {8, 2, 1};

    struct position p = select_position(nb, Xs, Ys);

    int posValide = 0;
    int i = 0;

    while (posValide == 0 && i < nb) {
        posValide = (p.X == Xs[i] && p.Y == Ys[i])? 1 : 0;
        ++ i;
    }
    
    if (posValide) {
        text_green();
        printf("    La position %d %d est une position valide\n", p.X, p.Y);
    } else {
        error ++;
        text_red();
        printf("    ERROR : La position %d %d n'est pas une position valide\n", p.X, p.Y);
    }

    text_white();
    printf("  Fin test select_position\n");
    return error;
}

int test_is_monocolor()
{
  printf("   Debut test is_monocolor\n");
  int error = 0;
  struct deck d;
  deck_init(&d);
  const struct tile *t_mono = d.cards[1].t;
  const struct tile *t_bi = d.cards[2].t;

  if (is_monocolor(t_mono) == 1)
    {
      text_green();
      printf("      La tuile monocolor est monocolor\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : La tuile monocolor n'est pas considéré monocolor\n");
    }

  if (is_monocolor(t_bi) == 0)
    {
      text_green();
      printf("      La tuile bicolor est bicolor\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : La tuile bicolor n'est pas considéré bicolor\n");
    }
  text_white();
  printf("    Fin test is_monocolor\n");
  return error;
}

int test_motifs()
{
  int error = 0;
  int taille = 3;
  int nb_players = 2;
  struct board b = board_init(taille, nb_players);
  
  struct deck d;
  deck_init(&d);
  
  const struct tile * t1 = d.cards[4].t;
  const struct tile * t2 = d.cards[1].t;
    
  struct position p1 = {.X=0, .Y=0};
  struct position p2 = {.X=0, .Y=1};
  struct position p3 = {.X=0, .Y=2};
  struct position p4 = {.X=1, .Y=0};
  struct position p5 = {.X=1, .Y=1};
  struct position p6 = {.X=1, .Y=2};
  struct position p7 = {.X=2, .Y=0};
  struct position p8 = {.X=2, .Y=1};
  
  
  place_tile(&b, t2, p1, 0, nb_players);
  place_tile(&b, t2, p2, 0, nb_players);
  place_tile(&b, t1, p3, 0, nb_players);
  place_tile(&b, t1, p4, 0, nb_players);
  place_tile(&b, t1, p5, 0, nb_players);
  place_tile(&b, t1, p6, 0, nb_players);
  place_tile(&b, t2, p7, 0, nb_players);
  place_tile(&b, t1, p8, 0, nb_players);
    
    /*
            plateau           
         V  |  V   |  V  
        V V | V V  | V R 
         V  |  V   |  R 
       ----------------
         V  |  V  |  V   
        V R | V  R| V R
         R  |  R  |  R   
       ---------------- 
         V  |  V   |     
        V V | V R  |    
         V  |  R   |     

    */

  printf("  Debut test motifs\n");

  // -------------------------------------------------
  printf("    Debut test monocolor_with_monocolor\n");
  if (motif_monocolor_with_monocolor(&b, 0, 0))
    {
      text_green();
      printf("      Il y a bien un motif monocolor à côté d'un monocolor en position (0, 0)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR :  Il ne détecte pas le motif monocolor en position (0, 0) \n");      
    }

  if (!motif_monocolor_with_monocolor(&b, 2, 0))
    {
      text_green();
      printf("      Il n'y a effectivement pas de motif monocolor en position (2, 0)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Il détecte un motif monocolor en position (2, 0)\n");
    }
  text_white();
  printf("    Fin test monocolor_with_monocolor\n");

  // ----------------------------------------------------
  
  printf("    Debut test monocolor_with_two_bicolor\n");
  if (!motif_monocolor_with_two_bicolor(&b, 0, 0))
    {
      text_green();
      printf("      Il n'y a pas de motif bicolor en position (0, 0)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Motif bicolor détecté en position (0, 0)\n");
    }
  
  if (!motif_monocolor_with_two_bicolor(&b, 2, 1))
    {
      text_green();
      printf("      Il n'y a pas de motif bicolor en position (2, 1) car pas monocolor\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Motif bicolor detecte en position (2, 1) alors que pas monocolor\n");
    }
  
  if (motif_monocolor_with_two_bicolor(&b, 0, 1))
    {
      text_green();
      printf("      Il y a un motif detecte en position (0, 1)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Motif bicolor non détecté en position (0, 1)\n");
    }
  
  text_white();
  printf("    Fin test monocolor_with_two_bicolor\n");
  // ------------------------------------------------------
  printf("    Debut test full_surrond\n");
  
  if (!motif_full_surrond(&b, 0, 1))
    {
      text_green();
      printf("      Il n'y a pas de motif surrounded en position (0, 1)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Il dé$etecte un motif surrounded en position (0, 1)\n");
    }
  
  if (motif_full_surrond(&b, 1, 1))
    {
      text_green();
      printf("      Il y a bien le motif surrounded en position (1, 1)\n");
    }
  else
    {
      error ++;
      text_red();
      printf("      ERROR : Il detecte un motif surrounded en position (1, 1)\n");
    }
  
  text_white();
  printf("    Fin test full_surrond\n");
  //--------------------------------------------------------
  
  printf("    Fin test motifs\n");
  return error;
}

int test_check_motif()
{
  printf("    Debut test check_motif\n");
  int error = 0;
  int taille = 3;
  int nb_players = 2;
  struct player players[2];
  init_players(2, players);
  
  struct board b = board_init(taille, nb_players);
  
  struct deck d;
  deck_init(&d);
  
  const struct tile * t1 = d.cards[4].t;
  const struct tile * t2 = d.cards[1].t;
    
  struct position p1 = {.X=0, .Y=0};
  struct position p2 = {.X=0, .Y=1};
  struct position p3 = {.X=0, .Y=2};
  struct position p4 = {.X=1, .Y=0};
  struct position p5 = {.X=1, .Y=1};
  struct position p6 = {.X=1, .Y=2};
  struct position p7 = {.X=2, .Y=0};
  struct position p8 = {.X=2, .Y=1};
  
  place_tile(&b, t2, p1, 1, nb_players);
  place_tile(&b, t2, p2, 1, nb_players);
  place_tile(&b, t1, p3, 0, nb_players);
  place_tile(&b, t1, p4, 0, nb_players);
  place_tile(&b, t1, p5, 0, nb_players);
  place_tile(&b, t1, p6, 0, nb_players);
  place_tile(&b, t2, p7, 1, nb_players);
  place_tile(&b, t1, p8, 0, nb_players);

  struct motif m1 = { .score = 3, .actif = 1, .test = &motif_monocolor_with_monocolor };
  struct motif m2 = { .score = 5, .actif = 1, .test = &motif_monocolor_with_two_bicolor };
  struct motif m3 = { .score = 10, .actif = 1, .test = &motif_full_surrond };

  struct motif motifs[3] = {m1, m2, m3};

  b.from_player[p1.X][p1.Y][0] = 0;
  b.from_player[p1.X][p1.Y][1] = 100;
  b.from_player[p2.X][p2.Y][0] = 0;
  b.from_player[p2.X][p2.Y][1] = 100;
  b.from_player[p3.X][p3.Y][0] = 100;
  b.from_player[p3.X][p3.Y][1] = 0;
  b.from_player[p4.X][p4.Y][0] = 100;
  b.from_player[p4.X][p4.Y][1] = 0;
  b.from_player[p5.X][p5.Y][0] = 100;
  b.from_player[p5.X][p5.Y][1] = 0;
  b.from_player[p6.X][p6.Y][0] = 100;
  b.from_player[p6.X][p6.Y][1] = 0;
  b.from_player[p7.X][p7.Y][0] = 0;
  b.from_player[p7.X][p7.Y][1] = 100;
  b.from_player[p8.X][p8.Y][0] = 100;
  b.from_player[p8.X][p8.Y][1] = 0;

    
    /*
          plateau           
         V  |  V  |  V  
        V1V | V1V | V0R 
         V  |  V  |  R 
       ----------------
         V  |  V  |  V   
        V0R | V0R | V0R
         R  |  R  |  R   
       ---------------- 
         V  |  V  |     
        V1V | V0R |    
         V  |  R  |     


    */

  checking_motif(players, &b, 3, motifs, nb_players);
  
  if (players[0].score == 10) {
    text_green();
    printf("      Le joueur 0 a bien un score de 10\n");
  } else {
    text_red();
    error ++;
    printf("      ERROR : Le joueur 0 a un score de %d au lieu de 10\n", players[0].score);
  }

  if (players[1].score == 16) {
    text_green();
    printf("      Le joueur 1 a bien un score de 16\n");
  } else {
    error ++;
    text_red();
    printf("      ERROR : Le joueur 1 a un score de %d au lieu de 16\n", players[1].score);
  }

  text_white();
  printf("    Fin test check_motif\n");
  return error;
}



int test_color_equals() {
    printf("  Debut test color_equals\n");
    int error = 0;
    struct color * cR1 = color_from_name("ROUGE");
    struct color * cR2 = color_from_name("ROUGE");
    struct color * cM = color_from_name("MAGENTA");

    if (color_equals(cR1, cR2)) {
        text_green();
        printf("    Deux couleurs rouges sont biens consideres comme egale\n");
    } else {
       error ++;
       text_red();
       printf("    ERROR : Deux couleurs rouges ne sont pas consideres comme egales les couleurs : %s %s\n",
         color_name(cR1), color_name(cR2));
    }

    if (! color_equals(cR1, cM)) {
        text_green();
        printf("    Deux couleurs rouge et magenta sont biens consideres comme non egale\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Deux couleurs rouge et magenta ne sont pas consideres comme non egales les couleurs : %s %s\n",
         color_name(cR1), color_name(cM));
    }

    text_white();
    printf("  Fin test color_equals\n");
    return error;
}

int test_parcours_en_profondeur(struct board * b) {
   printf("  Debut test parcours_en_profondeur\n");
   int error = 0;
   int nb_players = 2;
   struct zone_connexe z1 = {.nb_tuile = 0, .cases_players = {0}};   
   int connexe_used[MAX_BOARD_LONG][MAX_BOARD_LONG][5] = {{{0}}};
   for(int li=0; li< b->taille; li++) {
        for(int ci=0; ci< b->taille; ci++) {
            connexe_used[li][ci][4] = 0;
        }
    }
    parcours_en_profondeur(b, 0, 1, 0, connexe_used, &z1, nb_players);
    /*
        Test de la zone violette en partant de la case 0 1 au nord
    */

    if (z1.nb_tuile == 3) {
        text_green();
        printf("    La zone violette a bien 3 tuiles\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : La zone violette a %d tuile a lieu de 3\n", z1.nb_tuile);
    }

    if (z1.cases_players[0] == 200) {
        text_green();
        printf("    Le joueur 0 a bien 200 points niveau d'appartenance des tuiles dans la zone violette\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 0 a %d points niveau d'appartenance des tuiles au lieu de 200 dans la zone violette\n", z1.cases_players[0]);
    }

    if (z1.cases_players[1] == 150) {
        text_green();
        printf("    Le joueur 1 a bien 150 points niveau d'appartenance des tuiles dans la zone violette\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 1 a %d points niveau d'appartenance des tuiles au lieu de 150 dans la zone violette\n", z1.cases_players[1]);
    }

   struct zone_connexe z2 = {.nb_tuile = 0, .cases_players = {0}};   
   for(int li=0; li< b->taille; li++) {
        for(int ci=0; ci< b->taille; ci++) {
            connexe_used[li][ci][4] = 0;
        }
    }
    parcours_en_profondeur(b, 0, 2, 1, connexe_used, &z2, nb_players);
    /*
        Test de la zone rouge en partant de la case 0 2 au sud
    */

    if (z2.nb_tuile == 1) {
        text_green();
        printf("    La zone rouge a bien 1 tuile\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : La zone rouge a %d tuiles a lieu de 1\n", z2.nb_tuile);
    }

    if (z2.cases_players[0] == 100) {
        text_green();
        printf("    Le joueur 0 a bien 100 points niveau d'appartenance des tuiles dans la zone rouge\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 0 a %d points niveau d'appartenance des tuiles au lieu de 100 dans la zone rouge\n", z2.cases_players[0]);
    }

    if (z2.cases_players[1] == 0) {
        text_green();
        printf("    Le joueur 1 a bien 0 points niveau d'appartenance des tuiles dans la zone rouge\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 1 a %d points niveau d'appartenance des tuiles au lieu de 0 dans la zone rouge\n", z2.cases_players[1]);
    }

   struct zone_connexe z3 = {.nb_tuile = 0, .cases_players = {0}};   
   for(int li=0; li< b->taille; li++) {
        for(int ci=0; ci< b->taille; ci++) {
            connexe_used[li][ci][4] = 0;
        }
    }
    parcours_en_profondeur(b, 2, 1, 1, connexe_used, &z3, nb_players);
    /*
        Test de la zone rouge en partant de la case 2 1 au sud
    */

    if (z3.nb_tuile == 2) {
        text_green();
        printf("    La zone rouge a bien 2 tuile\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : La zone rouge a %d tuiles a lieu de 2\n", z3.nb_tuile);
    }

    if (z3.cases_players[0] == 100) {
        text_green();
        printf("    Le joueur 0 a bien 100 points niveau d'appartenance des tuiles dans la zone rouge\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 0 a %d points niveau d'appartenance des tuiles au lieu de 100 dans la zone rouge\n", z2.cases_players[0]);
    }

    if (z3.cases_players[1] == 150) {
        text_green();
        printf("    Le joueur 1 a bien 150 points niveau d'appartenance des tuiles dans la zone rouge\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : Le joueur 1 a %d points niveau d'appartenance des tuiles au lieu de 150 dans la zone rouge\n", z2.cases_players[1]);
    }
    
    text_white();
    printf("  Fin test parcours_en_profondeur\n");
    return error;
}

int test_connexe(struct board * b) {
    printf("  Debut test connexe\n");
    int error = 0;
    int nb_players = 2;
    struct player players[MAX_PLAYERS];
    init_players(nb_players, players);
    connexe(nb_players, players, b);

    int scores_attendus [2] = {10 ,4};
    for (int i = 0; i < nb_players; i ++) {
        if (players[i].score == scores_attendus[i]) {
            text_green();
            printf("    Le joueur %d a bien un score de %d\n", i, scores_attendus[i]);
        } else {
            error ++;
            text_red();
            printf("    ERROR : Le joueur %d a un score de %d au lieu de %d\n", i, players[i].score, scores_attendus[i]);
        }
    }

    text_white();
    printf("  Fin test connexe\n");
    return error;
}

int test_zonne_connexe()
{
    int nb_players = 2;
    int taille = 3;
    struct board b = board_init(taille, nb_players);

    struct deck d;
    deck_init(&d);

    const struct tile * t1 = d.cards[4].t;
    const struct tile * t2 = d.cards[1].t;
    const struct tile * t3 = d.cards[0].t;

    struct position p1 = {.X=1, .Y=1};
    struct position p2 = {.X=0, .Y=2};
    struct position p3 = {.X=0, .Y=1};
    struct position p4 = {.X=2, .Y=1};

    place_tile(&b, t1, p1, 0, nb_players);
    place_tile(&b, t1, p2, 0, nb_players);
    place_tile(&b, t2, p3, 1, nb_players);
    place_tile(&b, t3, p4, 1, nb_players);

    b.from_player[p1.X][p1.Y][0] = 100;
    b.from_player[p1.X][p1.Y][1] = 50;
    b.from_player[p2.X][p2.Y][0] = 100;
    b.from_player[p2.X][p2.Y][1] = 0;
    b.from_player[p3.X][p3.Y][0] = 0;
    b.from_player[p3.X][p3.Y][1] = 100;
    b.from_player[p4.X][p4.Y][0] = 0;
    b.from_player[p4.X][p4.Y][1] = 100;

    /*
            plateau           
            |  V  |  V  
            | V1V | V0R 
            |  V  |  R 
       ----------------
            |  V  |     
            | V0R |  
            |  R  |     
       ---------------- 
            |  R  |     
            | R1R |   
            |  R  |     
    */
    int error = 0;
    error += test_parcours_en_profondeur(&b);
    error += test_connexe(&b);
    return error;
}

int test_init_players() {
    printf("  Debut test init_players\n");
    int error = 0;
    int nb_players = 3;
    struct player players[MAX_PLAYERS];
    init_players(nb_players, players);
    
    for (int i = 0; i < nb_players; i ++) {
        if (players[i].score == 0) {
            text_green();
            printf("    Le joueur %d a bien un score de 0\n", i);
        } else {
            error ++;
            text_red();
            printf("    ERROR : Le joueur %d a un score de %d au lieu de 0\n", i, players[i].score);
        }
    }

    text_white();
    printf("  Fin test init_players\n");
    return error;
}

int test_update_propriete()
{
  printf("  Debut test update_propriete\n");
  int error = 0;
  int nb_players = 2;
  int taille = 3;
  struct board b = board_init(taille, nb_players);

  struct deck d;
  deck_init(&d);

  const struct tile * t1 = d.cards[4].t;
  const struct tile * t2 = d.cards[1].t;

  struct position p1 = {.X=1, .Y=1};
  struct position p2 = {.X=0, .Y=1};

  place_tile(&b, t1, p1, 0, nb_players);
  place_tile(&b, t2, p2, 0, nb_players);

  b.from_player[p1.X][p1.Y][0] = 0;
  b.from_player[p2.X][p2.Y][0] = 90;
  b.from_player[p2.X][p2.Y][1] = 50;

  update_propriete(&b, nb_players);

  /*
            plateau           
            |  V  |     
            | V V |     
            |  V  |    
       ----------------
            |  V  |     
            | V0R |  
            |  R  |     
       ---------------- 
            |     |     
            |     |   
            |     |     
    */

  if (b.from_player[p1.X][p1.Y][0] == 0) {
    text_green();
    printf("    Une influence de 0 n'est pas reduite a la fin de chaque tour\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Une influence de 0 a ete modifie a la fin du tour en %d\n", b.from_player[p1.X][p1.Y][0]);
  }

  if (b.from_player[p2.X][p2.Y][0] == 89) {
    text_green();
    printf("    Une influence de 90 a ete reduite a 89 a la fin du tour\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Une influence de 90 n a pas ete reduite a 89 a la fin du tour mais a%d\n", b.from_player[p2.X][p2.Y][0]);
  }

  if (b.from_player[p2.X][p2.Y][1] == 49) {
    text_green();
    printf("    Une influence de 50 a ete reduite a 49 a la fin du tour\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Une influence de 50 n a pas ete reduite a 49 a la fin du tour mais a %d\n", b.from_player[p2.X][p2.Y][1]);
  }

  if (b.from_player[0][0][0] == -1) {
    text_green();
    printf("    Une influence de -1 n'est pas reduite a la fin de chaque tour\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Une influence de -1 a ete modifie a la fin du tour en %d\n", b.from_player[0][0][0]);
  }

  text_white();
  printf("  Fin test update_propriete\n");
  return error;
}

int test_king()
{
  printf("  Debut test king\n");
  int error = 0;
  int nb_players = 2;
  int taille = 4;
  struct board b = board_init(taille, nb_players);

  struct deck d;
  deck_init(&d);

  const struct tile * t = d.cards[1].t;

  struct position p1 = {.X=0, .Y=0};
  struct position p2 = {.X=0, .Y=1};
  struct position p3 = {.X=1, .Y=1};
  struct position p4 = {.X=1, .Y=2};
  struct position p5 = {.X=2, .Y=2};
  struct position p6 = {.X=3, .Y=1};
  struct position p7 = {.X=3, .Y=2};

  place_tile(&b, t, p1, 0, nb_players);
  place_tile(&b, t, p2, 0, nb_players);
  place_tile(&b, t, p3, 0, nb_players);
  place_tile(&b, t, p4, 0, nb_players);
  place_tile(&b, t, p5, 0, nb_players);
  place_tile(&b, t, p6, 0, nb_players);

  b.from_player[p1.X][p1.Y][0] = 70;
  b.from_player[p2.X][p2.Y][0] = 70;
  b.from_player[p3.X][p3.Y][0] = 30;
  b.from_player[p4.X][p4.Y][0] = 60;
  b.from_player[p5.X][p5.Y][0] = 60;
  b.from_player[p6.X][p6.Y][0] = 60;
  b.from_player[p7.X][p7.Y][0] = 100;
  b.from_player[p1.X][p1.Y][1] = 70;
  b.from_player[p2.X][p2.Y][1] = 60;
  b.from_player[p3.X][p3.Y][1] = 20;

  /*
            plateau           
         V  |  V  |     |     
        V V | V V |     | 
         V  |  V  |     |
       -------------------------
            |  V  |  V  | 
            | V V | V V |
            |  V  |  V  | 
       -------------------------
            |     |  V  | 
            |     | V V |
            |     |  V  | 
       -------------------------
            |  V  |  V  | 
            | V V | V V |
            |  V  |  V  | 
    */

  king(&b, nb_players, p5.X, p5.Y);

  if (b.from_player[p5.X][p5.Y][0] == 10) {
    text_green();
    printf("    La case touche a bien ete reduite a 10\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case touche a ete reduite a %d au lieu de 10\n", b.from_player[p5.X][p5.Y][0]);
  }

  if (b.from_player[p4.X][p4.Y][0] == 10) {
    text_green();
    printf("    La case en haut a bien ete reduite a 10\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case en haut a ete reduite a %d au lieu de 10\n", b.from_player[p4.X][p4.Y][0]);
  }

  if (b.from_player[p7.X][p7.Y][0] == 50) {
    text_green();
    printf("    La case en haut a bien ete reduite a 50\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case en haut a ete reduite a %d au lieu de 50\n", b.from_player[p7.X][p7.Y][0]);
  }

  king(&b, nb_players, p6.X, p6.Y);

  if (b.from_player[p6.X][p6.Y][0] == 10) {
    text_green();
    printf("    La case touche a bien ete reduite a 10\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case touche a ete reduite a %d au lieu de 10\n", b.from_player[p6.X][p6.Y][0]);
  }

  if (b.from_player[p7.X][p7.Y][0] == 0) {
    text_green();
    printf("    La case a droite a bien ete reduite a 0\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case a droite a ete reduite a %d au lieu de 0\n", b.from_player[p7.X][p7.Y][0]);
  }

  if (b.from_player[p3.X][p3.Y][0] == 30) {
    text_green();
    printf("    La case en haut non connexe n'a pas ete reduite\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case en haut  non connexe ete reduite a %d au lieu de rester a 30\n", b.from_player[p3.X][p3.Y][0]);
  }

  king(&b, nb_players, p3.X, p3.Y);

  if (b.from_player[p3.X][p3.Y][0] == 0) {
    text_green();
    printf("    La case touche a bien ete reduite a 0 pour le proprietaire\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case touche a ete reduite a %d au lieu de 0 pour le proprietaire\n", b.from_player[p3.X][p3.Y][0]);
  }

  if (b.from_player[p3.X][p3.Y][1] == 20) {
    text_green();
    printf("    Un non proprietaire de la case touche n'a pas eu son influence modifie\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Un non proprietaire de la case touche a eu son influence modifie a %d au lieu de rester a 20\n", b.from_player[p3.X][p3.Y][1]);
  }

  if (b.from_player[p2.X][p2.Y][0] == 20) {
    text_green();
    printf("    La case en haut a bien ete reduite a 20 pour le proprietaire\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : La case en haute a ete reduite a %d au lieu de 20 pour le proprietaire\n", b.from_player[p2.X][p2.Y][0]);
  }

  if (b.from_player[p2.X][p2.Y][1] == 60) {
    text_green();
    printf("    Un non proprietaire de la case en haut n'a pas eu son influence modifie\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Un non proprietaire de la case en haut a eu son influence modifie a %d au lieu de rester a 60\n", b.from_player[p2.X][p2.Y][1]);
  }

  king(&b, nb_players, p1.X, p1.Y);

  if (b.from_player[p1.X][p1.Y][0] == 20 && b.from_player[p1.X][p1.Y][1] == 20) {
    text_green();
    printf("    Les deux proprietaires de la case touche ont bien eu lors influence reduite a 20\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Lex deux proprietaire non pas eu influence de 20 : p1 = %d; p2 = %d\n", 
    b.from_player[p1.X][p1.Y][0], b.from_player[p1.X][p1.Y][1]);
  }

  if (b.from_player[p2.X][p2.Y][0] == 0 && b.from_player[p2.X][p2.Y][1] == 10) {
    text_green();
    printf("    Les deux proprietaires de la case touche ont bien eu lors influence reduite a 0 et 10\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR : Lex deux proprietaire non pas eu influence de 0 et 10 : p1 = %d; p2 = %d\n", 
    b.from_player[p2.X][p2.Y][0], b.from_player[p2.X][p2.Y][1]);
  }

  text_white();
  printf("  Fin test king\n");
  return error;
}

int execute_test_rule()
{
    printf("Debut test rule.c\n");
    int error_board_init = test_board_init();
    int error_auth = test_authorized_places();
    int error_pos_val = test_position_valide();
    int error_place_tile = test_place_tile();
    int error_select_pos = test_select_position();
    int error_is_mono = test_is_monocolor();
    int error_test_motifs = test_motifs();
    int error_check_motif = test_check_motif();
    int error_color_equals = test_color_equals();
    int error_init_players = test_init_players();
    int error_zonne_co = test_zonne_connexe();
    int error_update_pro = test_update_propriete();
    int error_king = test_king();
    int error_tot = error_board_init + error_auth + error_pos_val + error_place_tile + error_select_pos + error_is_mono
     + error_test_motifs + error_check_motif + error_color_equals + error_init_players + error_zonne_co + error_update_pro
     + error_king;

    display_error(error_board_init, "de board_init");
    display_error(error_auth, "de authorized_places");
    display_error(error_pos_val, "de position_valide");
    display_error(error_place_tile, "de place_tile");
    display_error(error_select_pos, "de select_position");
    display_error(error_is_mono, "de is_monocolor");
    display_error(error_test_motifs, "des motifs");
    display_error(error_check_motif, "de check_motif");
    display_error(error_color_equals, "de color_equals");
    display_error(error_init_players, "de init_players");
    display_error(error_zonne_co, "des zones connexes");
    display_error(error_update_pro, "de update_propriete");
    display_error(error_king, "de king");
    display_error(error_tot, "de rule");

    text_white();
    printf("Fin test rule.c\n");
    printf("-----------------------------------------\n");
    printf("\n");
    return error_tot;
}
