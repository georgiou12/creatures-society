README for askisi3

Εντολη μεταγλωτισης:g++ -o society main.cpp creatures.cpp creatures.h
Εντολες εκτελεσης:  ./society 5 30 2 4 4
                    ./society 10 30 5 7 6
                    ./society 4 16 1 2 2
                    ./society 3 25 5 6 6
                    ./society 8 40 10 12 11

MAIN:
~Στo main.cpp file αρχικα δεχομαι 5 τιμες απο την γραμμη εντολης και τις τοποθετω με σειρα στις μεταβλητες 
N,M,L,good_thrsh,bad_thrsh. Επισης δηλωνω int μεταβλητες action,place που θα της χρησιμοποιησω μεσα σην for
για να τις τυχαιες τιμες. Δημιουργω ενα αντικειμενο mysociety της creature_society και περναω τις μεταβλητες
N,L,good_thrsh,bad_thrsh σαν παραμετρους. Οριζω την srand με βαση τον χρονο time(NULL). Κανω Μ πραξεις (beat,
bless). Μεσα στην for η action παιρνει τιμη 1 ή 2 για beat ή bless αντιστοιχα και η place τιμες απο 0 μεχρι
Ν(συνολο πλασματων στην mysociety)-1, μεσω της rand. Εξω απο την for εμφανιζουμε με τις no_of_good και 
no_of_zobies τα μηνυματα που ζητουνται.

CREATURES.CPP:
~Στο creatures.cpp file δηλωνω ορισμενες απο τις συμπεριφορες των κλασεων μου: 
->creature_society-constructor:με initializer list το crowd γινεται N. Δημιουργω δυο const char* πινακες [26] με καθε στοιχειο να αποτελειται
απο ενα γραμμα μικρο η κεφαλαιο με ονοματα good,bad. Παλι δηλωνω την srand οπως πριν και εναν double pointer society
σε creatute, οπου τον οριζω σαν πινακα δεικτων Ν μεγεθους δυναμικα και βαζω τον crpointer(double pointer) να δειχνει
στην αρχη του. Επειτα μεχρι i η j θα παιρνει τιμες απο 0 εως 25 και η για να επιλεγεται απο τους πινακες ποιο κελι θα
χτησιμοποιηθει και μια ran που παιρνει τιμες 1 ή 2 για το αν θα δημιουργησω good η bad creatures στην επομενη θεση της
society. Αφου οι κλασεις good_creature,bad_creature ειναι υποκλασεις της creature εχω τους pointers σε creature για να 
εχω μες το society μου και τα δυο ειδη υποκλασεων. Περναω τα ιδια ορισματα και στις δυο με διαφορα οτι αναλογα την ran
περναω το good[j],bad[j] και ομοια την good_thrsh ή bad_thrsh.
->clone_next:αν το i(παραμετρος που δεχεται για την θεση) ειναι με την τελευταια τοτε κλωνοποιουμε στην πρωτη θεση της 
society αν εκει βρισκεται ζομπι, αλλιως στην επομενη της i, μεσω της συναρτησης clone της creature.
->clone_zobies: οσο το επομενο craeture της society δεν ειναι zobie και το i δεν φτανει μια θεση πριν την τελευταια τοτε
παλι μεσω της clone του creature κλωνοποιουμε στην επομενη θεση της society.
->no_of_good & no_of_zobies: επιστρεφουν αντιστοιχα εναν int που δηλωνουν ποσα καλα πλασματα και ζομπι ατιστοιχα υπαρχουν
στην society μας.

->good_creature-bless:αν δεν ειναι ζομπι αυξανεται η ζωη του κατα μια μοναδα και αν ειναι μεγαλυτερη της μεταβλητης 
good_thrsh τοτε καλειται η clone_next της creature_society για να κλωνοποιηθει στην επομενη θεση μονον αν εκει υπαρχει
ζομπι.
->good_creature-clone: επιστρεφει εναν δεικτη σε craeture που τοποθετειται μεσω της clone_next στο κελι της society 
στο οποιο κλωνoποιω. Οριζω νεο δεικτη σε creature. Αν το creature απο το οποιο κανω κοπι ειναι good κανω new ενα good
creature αλλιως ενα bad. Το τσεκαρω αυτο διοτι η μου καλειται σε creature->good/bad και παντα θα δημιουργει το ιδιο 
ειδος creature με αυτο που θελω να κλωνοποιησω πανω του.
->bad_creature-bless & clone:ιδια διαδικασια με αυτα της good_creature απλα καλω την clone_zobies αντι της clone_next.
->destructors: ειναι virtual οπως και της superclass creature και διαγραφουν το ονομα και τον pointer σε society.

CREATURES.H:
~Εδω δηλωνω τις κλασεις μου με τα χαρακτηριστικα τους και τις inline functions τους:
->creature:εχει τα χαρακτηριστικα απου ζητουνται με μια εξτρα μεταβλητη την pos που δεινχει την θεση της society στην οποια
ειναι αποθηκευεμενο το εν λογω αντικειμενο creature, και ο δεικτης σε creature_society δειχνει στην society που ανηκουν.
δηλωνω σαν pure virtual τις blees,beat,get_thrsh,is_a_good καθως και τον destructor της creature. O constructor της creature
δεχεται ενα ονομα,την θεση στην οποια βρισκεται, την ζωη και τον δεικτη στο society που ανηκει και τα αρχικοποιει με initializer
list εκτος του ονοματος που χρησιμοποιω τις συναρτησεις strcpy,strlen της βιβλιοθηκης cstring. Το pos θα χρησιμευσει και για την 
μοναδικοτητα που ζητηθηκε με την εκτυπωση του μετα το ονομα του creature. Επισης εχω και τις συναρτησεις get->name,pointer,life,
pos που επιστρεφουν τις τιμες που εκφραζουν και θα χρησιμευσουν στον constructor των good,bad creature.
->good_creature-bad_creature:ειναι και οι δυο υποκλασεις της creature, εχουν εκαστες απο μια int μεταβλητη good-bad xx_thrsh 
αντιστοιχα για το "κατωφλι". οι constructors τους δεχονται τα ιδια με της creature για να γινει μεσω initializer list με τον 
constructor της creature το νεο creature που απαιτειται για την δημιουργια και των δυο υποκλασεων καθως και μια τιμη αναλογα 
για να τοποθετησουν στις μεταβλητες "κατωφλι".
->Οι bless και των δυο εχουν αναπτυχθει στο .cpp αρχειο ενω οι beat αμφοτερων μειωνουν κατα μια μοναδα την ζωη του creature αν δεν
ειναι zobie. Και η virtual is_a_good επιστρεφει true αν ειμαι στο good_creature αλλιως false για το bad_creature, ενω τα get_thrsh 
επιστρεφουν το good ή bad thrsh αντιστοιχα.
->creature_society: εχει το crowd για το πληθος creature στην society μας και δυο double pointers σε creature για τον πινακα δεικτων 
σε creaturesκαι την αρχη της society (society και crpointer αντιστοιχα). Ο constructor της παιρνει τεσσερις τιμες int. Οι bless και 
beat παιρνουν μια int και για το iοστο creature με αρχη το crpointer καλουν τις αντιστοιχες bless και beat, ενω ολες οι υπολοιπες
functions εχουν χαρακτηριστει στο .cpp αρχειο.


Ουσιαστικα εχω χρησιμοποιησει για την υλοποιηση της ασκησης εναν συνδιασμο των δυο τελευταιων bullet της εκφωνησης προσθετοντας και
την θεση που ανηκει το καθε creature στο εσωτερικο του για να την χρηση του στην μοναδικοτητα αλλα και εχοντας εναν δεικτη στην society
μου ως ενα αλλο χαρακτηριστικο. Με τον συνδιασμο αυτων των δυο καταφερνω ετσι να περναω απο την creature_society::clone_next,clone_zobies
στην clone των good-bad_creature.
Επισης εμφανιζω το μηνυμα "this is a dead society" αν ολα τα πλασαματα ειναι ζομπι στο society μου αν και δεν ημουν σιγουρος βαση εκφωνησης 
αν αυτο ζητουνταν.