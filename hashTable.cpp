#include <iostream>
using namespace std;


class hashNode{
    public:
        int anahtar;
        hashNode *pSonraki;
        hashNode(int anahtar){
            this -> anahtar = anahtar;
            pSonraki = NULL;
        }
};

class hashTable{
    public:
        int elemanSayisi;
        hashNode *table[10];

        hashTable(){
            elemanSayisi = 0;
            for(int i=0; i<10; i++)    table[i] = NULL;
        }

        void ekle(int anahtar){
            hashNode *node = new hashNode(anahtar); //girilen anahtari tutan bir dugum olusturuyoruz.
            int mod = anahtar % 10;    //anahtarlari birler basamagina gore tabloya yerlestiriyoruz.

            //girilen anahtarin tabloda var olup olmadiginin kontrolu
            for(int i=0; i<10; i++){
                hashNode *pTemp = table[i];

                while(pTemp != NULL){

                    if(pTemp -> anahtar == anahtar){
                        cout << "anahtar tabloda var..!" << endl;
                        return;
                    }
                    pTemp = pTemp -> pSonraki;
                }
            }

            //belirtilen indiste bir dugum yoksa
            if(table[mod] == NULL){
                table[mod] = node;  //olsuturdugumuz dugumu tabloda istenilen yere koyduk
                cout << anahtar << " tabloya eklendi." << endl;
                elemanSayisi++;
            }
            
            //belirtilen indiste bir dugum varsa
            else{
                hashNode *pTemp = table[mod];
                //listenin sonuna kadar gidiyoruz
                while(pTemp -> pSonraki != NULL)    pTemp = pTemp -> pSonraki;
                pTemp -> pSonraki = node;   //olusturdugumuz dugumu toblada istenen yere koyduk
                elemanSayisi++;
                cout << anahtar << " tabloya eklendi." << endl;
            }
        }

        void sil(int anahtar){
            //table uzerinde haraket etmemizi saglayacak for dongusu.
            for(int i=0; i<10; i++){
                hashNode *izci = NULL;  hashNode *takipci = NULL;   //izci ve takipcileri olusturuyoruz.

                //tablodaki belirtilen indis bos degilse.(bossa zaten silecek birsey yoktur o yuzden else'e gerek yok)
                if(table[i] != NULL){
                    izci = table[i];    //izci listenin ilk elemanindan basliyor
                    takipci = izci;     //tkaipci listein ilk elemanindan izciyi takibi basliyor

                    //tabloda bulanan her bir listenin uzerinde haraket etmemizi saglayacak while dongusu.
                    while(izci != NULL){

                        //listenin ilk elemani silinecek ise
                        //ilk eleman silinirken takipci ilk elemanin gerisinde olamaz bu durumda ilk eleman farkli sekilde silinmeli.
                        if(izci -> anahtar == anahtar && izci == table[i]){
                            table[i] = table[i] -> pSonraki;    //listenin ikinci elemanini birinci elemanin uzerine yaziyoruz
                            elemanSayisi--;
                            cout << anahtar << " silindi" << endl;
                            return;
                        }

                        //silmek istedigimiz anahtari bulduysak.
                        else if(izci -> anahtar == anahtar){
                            izci = izci -> pSonraki;    //takipci yerinde kaliyor izci bir adim ileri gidiyor.
                            takipci -> pSonraki = izci; //takipci nin pSonraki izciyi gosterirse silinecek elemani atlamis oluyoruz.
                            elemanSayisi--; 
                            cout << anahtar << " silindi" << endl;
                            return;  //while dongusunden cikmak icin
                        }
                        takipci = izci; //takipci izcinin yanina geliyor.
                        izci = izci -> pSonraki;    //izci bir ileri gidiyor.
                    }
                }
            }
            cout << "listede " << anahtar << " anahtari bulunamadi. Silme islemi gerceklestirilemiyor..!" << endl;
        }

        void elemanlariGoster(){
            //tabloda eleman var ise
            if(elemanSayisi > 0){
                //tablodaki indisleri geziyor
                for(int i=0; i<10; i++){
                    hashNode *pTemp = table[i]; //gecici pointer
                    //indisdeki listeyi geziyor
                    while(pTemp != NULL){
                        cout << pTemp -> anahtar << endl;   //anahtari ekrana basiyor
                        pTemp = pTemp -> pSonraki;  //sonraki elemana geciyor
                    }
                }
            }
            else{
                cout << "tablo bos..!" << endl;
            }
            
        }

        void temizle(){
            for(int i=0; i<10; i++)
                table[i] = NULL;    //tablodaki her elemani null yapiyoruz
            elemanSayisi = 0;
        }

        int getElemanSayisi(){  return elemanSayisi;}

};

void cirpilamaUygulamasi(bool &donguDevam, hashTable &tablo){
    system("cls");
    cout << "    Cirpilama(Hash Tablo) Uygulamasi" << endl;
    cout << "1-> tabloya eleman ekle\n2-> tablodan eleman cikar\n";
    cout << "3-> tabloyu temizle\n4-> tablodaki eleman sayisini goster\n";
    cout << "5-> tablodaki elemanlari goster\n";
    cout << "6-> ana menuye don\n";
    cout << "yapmak istediginiz islem: ";   int girdi;  cin >> girdi;
    system("cls");
    switch (girdi)
    {
        case 1: 
            cout << "tabloya eklemek istediginiz sayiyi girin: ";
            int girdi2; cin >> girdi2;  tablo.ekle(girdi2);
            system("pause");    break;
        case 2:
            cout << "silmek istediginiz anahtari girin: ";
            cin >> girdi2;  tablo.sil(girdi2);
            system("pause");    break;
        case 3: 
            cout << "tablo temizlendi..!" << endl;  tablo.temizle();
            system("pause");    break;
        case 4:
            cout << "tabloda " << tablo.getElemanSayisi() << " adet eleman var." << endl;
            system("pause");    break;
        case 5:
            tablo.elemanlariGoster();   system("pause");    break;
        case 6: donguDevam = false;    break;
        default:    cout << "hatali giris yaptiniz tekrar deneyin..!\n";  system("pause");  break;
    }
}

int main(){

    hashTable tablo;

    bool donguDevam = true;

    while (donguDevam)
        cirpilamaUygulamasi(donguDevam,tablo);
    
}