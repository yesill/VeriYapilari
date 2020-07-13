#include <iostream>
using namespace std;


class node{
    public:
        int veri;       //dugumun girilen veriyi tutan kismi.
        node *pOnceki;  //giris de onceki eleman mantigini tercih ettigimden bahsetmistim.  //adres bolumu!!!
        //constructor a ihtiyac duymadim.
};

/*  Tek yonlu bagli liste;
    tek yonlu bagli liste de cikarma islemini, cikartmak istedigimiz degeri girerek yaptirmayi tercih ettim.
    aradan veya sondan cikarma yapmak yerine cikarmak istedigimiz veriyi giriyoruz. O veri basta, sonda, arada
    fark etmeksizin lsiteden sorunsuzca cikartiliyor.
*/
class list{
    int elemanSayisi;
    node *pTemp;    //son elemanin adresini tutuyor.
    public:
        list(){
            elemanSayisi = 0;   //yeni lsite bos olmali.
            pTemp = NULL;   //bir nevi top deger.
        }
        void ekle(int deger, int index){    //girilen index te yeni bir dugum olusturup, girilen veriyi bu dugume atiyor.
            /*  indis aslinda yoktur islemlerin daha kolay yapilmasi icin varmis gibi davraniyoruz.
                orn: 5 elemanli bir lsitenin 1. indisine yeni bir eleman ekleyecegiz. ekleme isleminden once 1. indiste 
                bulunan elemanin pOnceki'si 0. indisteki elemani gosteriyor, yeni ekledegimiz elemanin pOnceki'sini,
                mevcut elemanin pOnceki'sine esitliyoruz. sonra mevcutta 1.indiste olan elemanin pOnceki'sine yeni eklenen
                elemanin adresini atarak ekleme islemini bitiriyoruz.
            */
            node *pIzci = pTemp, *pTakipci = pIzci; //pTemp in degismemesi icin. takipci bos durmasin diye.
            node *n = new node; //eklenecek dugumu olusturduk.
            n -> veri = deger;  //girilen degeri veriye atadik.
            //ilk elemani ekleme.
            if(index == 0 && elemanSayisi == 0){
                n -> pOnceki = NULL;    //ilk eleman oldugu icin oncesinde gosterecek eleman yok.
                pTemp = n;  //ilk elemani gosteriyor.
                elemanSayisi++;
            }
            //listenin basina ekleme.
            else if(index == 0 && elemanSayisi != 0){   //lsitenin basi ama liste bos degil.
                for(int adim = 1; adim <= (elemanSayisi -1); adim++){
                    pIzci = pIzci -> pOnceki;   //istenilen indise vardik.
                }
                n -> pOnceki = NULL;    //ilk eleman oldugu icin kendisinden once bir elemani gosteremez.
                pIzci -> pOnceki = n;   //izci eski ilk eleman. pOnceki olarak, yeni elemani(n) gosterirse n ilk eleman olur.
                elemanSayisi++;
            }
            //lsite sonuna ekleme.
            else if(index == elemanSayisi){
                n -> pOnceki = pIzci;   //yeni eklenen eleman en sondaki elemani gosteriyor.(pTemp)
                pTemp = n;  //pTemp listenin sonuncu elemanini gosterir. bu durumda yeni eklenen elemani(n)
                elemanSayisi++; //ekleme islemi oldugu icin eleman sayimizi arttirdik.
            }
            //listenin arasina ekleme.
            else{
                /*
                    5 elemanli bir lsitenin 1. indisine yeni bir eleman ekleyecegiz. 5 -1 den en buyuk indis 4.
                    1. indise varmak icin geri gitmemiz gerek adim sayisi: (en buyuk indis) - (istenilen indis) = 3.
                    ((eleman sayisi -1) - index) = (adim sayisi);
                */
                for(int adim = 1; adim <= ((elemanSayisi -1) - index); adim++){
                    pIzci = pIzci -> pOnceki;   //istenilen indise vardik.
                }
                //yeni eklenen elemanin(n) yerinde daha once bulunan elamanin pOnceki'si n'nin yeni pOnceki'si olmali.
                n -> pOnceki = pIzci -> pOnceki;
                //eskiden ayni indiste bulunan elemanin pOnceki'si artik yeni elemani gosteriyor. bir yuakri kaymis oldu.
                pIzci -> pOnceki = n;
                elemanSayisi++; //ekleme islemi oldugu icin eleman sayimizi arttirdik.
            }
        }
        void cikar(int index){
            //izci - takipci kullandik. izci listede bir onceki iteme gectigi zaman, takipci onun bir adim gerisinden geliyor.
            node *pIzci = pTemp;    //pTemp degerinin degismeden kalmasi icin.
            node *pTakipci = NULL;  //aciklama altta
            /*  
                Listemizde 3 eleman olsun A,B,C. B yi silmek istersek, C dugumunun adres kismi(pOnceki)
                B yi gosteriyor. C nin adres kismina A nin adresini atarsak, B yi listeden cikarmis oluruz.
                C -> pOnceki = A
                B yi cikarirken C ye ihtiyacimiz var oyuzden "pTakipci" pointeri var.
                pIzci onden gidip B ye indiginde, pTakipci C yi gosteriyor olacak.              
            */
            //en son indisteki elemani cikarma.
            if (index == elemanSayisi-1){
                pIzci = pIzci -> pOnceki;   //takipci, C olmadigi icin B de, izciyi B den A ya indiriyoruz.
                pTemp = pIzci;  //B yi silmek icin listenin yeni sonuncu elamanini(A) pTemp e atiyoruz.
                elemanSayisi--;
            }
            //ilk elemani cikarma.
            else if(index == 0){
                for(int adim = 1; adim <= elemanSayisi-1; adim++){
                    pTakipci = pIzci;   //takipci 1 adim arkadan geliyor.
                    pIzci = pIzci -> pOnceki;   //istenilen indise vardik.
                }
                //0. indsiteki elemanin pOnceki'si NULL olur. Eger 1. indisteki elemanin pOncekisi'ni NULL yaparsak 0.indis olmus olur.
                pTakipci -> pOnceki = NULL;
                elemanSayisi--;
            }
            //aradan elaman cikarma.  
            /*
                5 elemanli bir lsitenin 1. indisine yeni bir eleman ekleyecegiz. 5 -1 den en buyuk indis 4.
                1. indise varmak icin geri gitmemiz gerek adim sayisi: (en buyuk indis) - (istenilen indis) = 3.
                ((eleman sayisi -1) - index) = (adim sayisi);
            */
            else{
                for(int adim = 1; adim <= (elemanSayisi-1) - index; adim++){
                    pTakipci = pIzci;   //takipci 1 adim arkadan geliyor.
                    pIzci = pIzci -> pOnceki;   //istenilen indise vardik.
                }
                pIzci = pIzci -> pOnceki;   //takipci C de, Izciyi B den, A ya indiriyoruz.
                pTakipci -> pOnceki = pIzci;    //C nin pOnceki sine A yi attik. boylece B devre disi kaldi.
                elemanSayisi--;
            }
        }
        //son eklenen elemani null yaparsak liste temizlenmis olur, sondan basa gidiyoruz ve "son" artik yok.
        void temizle(){ pTemp = NULL;   elemanSayisi = 0;}
        void yazdirElemanlar(){
            node *pYazici = pTemp;
            int indexSayaci = elemanSayisi-1;    //gorsellik icin.
            while(pYazici != NULL){
                cout << indexSayaci << ". >\t" << pYazici -> veri << endl;
                pYazici = pYazici -> pOnceki;
                indexSayaci--;
            }
        }
        int getElemanSayisi(){ return elemanSayisi;}
};

void listeUygulamasi(bool &donguDevam, list &liste){
    system("cls");
    cout << "    Liste Uygulamasi" << endl;
    cout << "1-> listeye eleman ekle\n2-> listeden eleman cikar\n";
    cout << "3-> listeyi temizle\n4-> listedeki elemanlari goster\n";
    cout << "5-> listedeki eleman sayisini goster\n6-> ana menuye don\n";
    cout << "yapmak istediginiz islem: ";   int girdi;  cin >> girdi;
    system("cls");
    switch(girdi){
        case 1: {
            bool disariDonguDevam = true;
            while(disariDonguDevam){
                system("cls");
                cout << "1-> araya eleman ekle\n2-> sona eleman ekle\n3-> ana menuye don\nyapmak istediginiz islem: ";
                int girdi2; cin >> girdi2;
                //araya eleman ekleme;
                if (girdi2 == 1){
                    while(true){
                        system("cls");
                        liste.yazdirElemanlar();
                        cout << "yeni elemani kacinci siraya eklemek istiyorsunuz?\nSectiginiz sirada baska bir eleman varsa";
                        cout << "o eleman bir sira yukariya kaydirilir.\nelamani eklemek istediginiz sira numarasi: ";
                        int girdi3;    cin >> girdi3;
                        if (0 <= girdi3 && girdi3 <= liste.getElemanSayisi()){
                            system("cls");  cout << "sira numarasi: " << girdi3;
                            cout << "\nEklemek istediginiz veri(tam sayi): ";
                            int girdi4; cin >> girdi4;  //kullanicidan veriyi aliyoruz.
                            liste.ekle(girdi4, girdi3); //deger, index
                            system("cls");  //gorsellik  
                            cout << girdi4 << " degeri, " << girdi3 << ". siraya eklendi.\n";
                            disariDonguDevam = false;   system("pause");    //disasriDongu kirildi.
                            break;  //iceri dongu kirildi;
                        }
                        else{
                            system("cls");  //gorsellik
                            cout << " 0 < sira numarasi < " << (liste.getElemanSayisi() + 1) << " olmali..!\n";
                            system("pause");    break;  //iceri dongu kirildi ama disari dongu kirilmadi..!
                        }
                    }
                }
                //sona eleman ekleme;
                else if(girdi2 == 2){
                    system("cls");
                    cout << "eklemek istediginiz veriyi girin: ";   int girdi3; cin >> girdi3;
                    //en buyuk indis eleman sayisindan bir az olur. eleman sayisini gonderirsek yeni bir indis olusturur.
                    liste.ekle(girdi3, liste.getElemanSayisi());
                    cout << girdi3 << " listenin sonuna eklendi.\n";    system("pause");    break;
                }
                //ana menuye don;
                else if(girdi2 == 3){
                    system("cls");  disariDonguDevam = false;   //disari dongu kirildi.
                    break;  //iceri dongu kirildi.
                }
                //hatali giris;
                else{
                    system("cls");  cout << "hatali giris lutfen tekrar deneyin..!" << endl;    
                    system("pause");    continue;   //ekleme menusune donuyor.
                }
            }
            break;
        }
        case 2: {
            if (liste.getElemanSayisi() == 0){
                cout << "liste bos oldugu icin cikarma islemi yapilamiyor..!\n";
                system("pause");
            }
            else{
                while(true){
                    liste.yazdirElemanlar();    cout << "\ncikarmak istediginiz elemanin sira numarasi: ";
                    int girdi2; cin >> girdi2;
                    if (0 <= girdi2 && girdi2 <= liste.getElemanSayisi()){
                        liste.cikar(girdi2);    cout << girdi2 << " listeden cikarildi.\n";
                        system("pause");    break;
                    }
                    else{
                        cout << "hatali giris yaptiniz..!\n";
                        cout << "0 <= sira numarasi <= " << liste.getElemanSayisi() << " arasinda olmali..!\n";
                        system("pause");    continue;
                    }
                }
            }
            break;
        }
        case 3: liste.temizle();    cout << "liste temizlendi.\n";  system("pause");    break;   
        case 4: {
            if(liste.getElemanSayisi() == 0){  cout << "liste bos..!\n";   system("pause");}   //eleman sayisi 0 ise lsite bos.
            else{   
                liste.yazdirElemanlar();    
                cout << "\nlistede " << liste.getElemanSayisi() << " adet elaman bulunuyor.\n"; 
                system("pause");
            }   break;  //eleman sayisi 0 degilse elemanlari ekrana yazdir.
        }
        case 5: cout << "listede " << liste.getElemanSayisi() << " adet elaman bulunuyor.\n"; system("pause");    break;
        //donguDevam false olursa fonksiyonu icine alan while dongusu kirilmis olacak.
        case 6: donguDevam = false;    break; 
        default:    cout << "hatali giris yaptiniz tekrar deneyin..!\n";  system("pause");  break;
    }
}

int main(){

    list liste;

    bool donguDevam = true;

    while (donguDevam)
        listeUygulamasi(donguDevam,liste);
    
}