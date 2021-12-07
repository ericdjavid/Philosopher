# :pray: PHILOSOPHER PROJECT :pray:

## Description du projet :bookmark_tabs: 
Le projet est une introduction au multithreading et aux mutex. L' idée est que des philosophes se réunissent autour d'une table. Ils peuvent manger, dormir, et penser. Pour manger, il leur faut 2 fourchettes, sachant qu'il y a une fourchette entre chaque philosopher (qui sont par ailleurs des mutex) . Le philosophe mange [TTE], se repose [TTS] puis pense tant qu'il n'y a pas suffisamment de fourchettes disponibles (2) pour qu'il recommence à manger. Si le philo n'a pas recommencé à manger avant, il meurt, I' objectif étant qu' ils vivent le plus longtemps possible, en fonction des paramèt res renseignés lors du lancement du programme. 

## Methodologie :fountain_pen:
Une structure de controle contenant les paramètres parsés 
Une structure de philosophe, contenant les éléments propres aux philo (e.g. le "thread et le mutex correspondant à sa fourchette (de gauche) + un pointeur vers la fourchette de droite (qui appartient à son voisin Ît nécessaire car les philo ne peuvent emprunter une fourchette qu'à leur voisin).
Je crée une liste chainée de structure de hilosophes et chaque philo fait l'objet d'un thread qui appelle la fonction "ft_live" 
Dans la fonction de vie, un sous-thread est créé pour monitorer la "mort" (attention à bien prendre le moment où le philo commence à manger et non le moment où il finit. 

## Faire fonctionner le code :hammer_and_wrench: 
- git clone https://github.com/ericdjavid/Philosopher.git
- make 
- ./philo [nb_phiIo] [time_to_die] [time_to_eat] [optionnal: nb_of_eating_cycles]

## Testeur 
- https://github.com/MicheIIeJiam/LazyPhiIosophersTester 

![edjv](/philo.png)
