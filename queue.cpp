#include <iostream>
using namespace std;

class node{
    public:
        int veri;       //dugumun girilen veriyi tutan kismi.
        node *pOnceki;  //onceki eleman mantigini tercih ettim.
};

class queue{
    int elemanSayisi;
    node *pTemp;
    public:
        queue(){
            elemanSayisi = 0;   //yeni kuyruk bos olmali.
            pTemp = NULL;   //bir nevi top deger.
        }
        void ekle(int deger){
            node *n = new node();   //yeni bir dugum olusturuyoruz.
            n -> veri = deger;  //girilen degeri dugumdeki veri ye esitliyoruz.
            n -> pOnceki = pTemp;   //listedeki bir onceki dugumun adresini yeni dugumun adres bolumune(pOnceki) atiyoruz.
            pTemp = n;  //pTemp i yeni girilen dugume esitliyoruz ki bir sonraki dugumde kullanabilelim.
            elemanSayisi++; //ekleme yaptigimiz icin eleman sayisini artiriyoruz.
        }
        void cikar(){
            //izci - takipci kullandik. izci listede bir onceki iteme gectigi zaman, takipci onun bir adim gerisinden geliyor.
            node *pIzci = pTemp;   //pTemp in degismemesi icin dongude pIzci pointer ini kullaniyoruz.
            node *pTakipci = pTemp;  //listeye cikarttigimiz elemandan sonra eklenen elemanin adres bolumunu(pOnceki) NULL yapmak icin.
            
            while(true){    //sonsuz dongu. cikis if icerisinde break le yapilacak.
                if (pIzci -> pOnceki == NULL){    //ilk terime geldik.
                    /*
                        kuyruk veri yapisinda ilk giren terim ilk cikar oyuzden ilk terime kadar geldik.
                        listeye cikarttigimiz elemandan sonra eklenen elemanin adres bolumunu(pOnceki)
                        NULL yaparsak, listenin ilk elemani o olacaktir.
                    */
                   pTakipci -> pOnceki = NULL;
                   elemanSayisi--;
                   break;   //cikartma islemini yaptik artik donguden cikiyoruz.
                }
                else{   //pIzci -> pOnceki != NULL
                    pTakipci = pIzci;   //pTakipci bir adim devam etmis oldu.
                    pIzci = pIzci -> pOnceki;   //pIzci de bir adim devam etmis oldu.
                }
            }
        }
        //son eklenen elemani null yaparsak liste temizlenmis olur, sondan basa gidiyoruz ve "son" artik yok.
        void temizle(){ pTemp = NULL;   elemanSayisi = 0;}  //pTemp(top) bossa(NULL) liste bos demektir.
        void yazdirElemanlar(){
            node *pYazici = pTemp;  //pTemp in degismemesi icin.
            int sayac = 0;   //gorsellik icin.
            while(pYazici != NULL){
                cout << pYazici -> veri;    //mevcut elemanin icindeki veriyi yazidiriyoruz.
                sayac++;    //gorsellik icin.
                if (sayac < elemanSayisi)  cout << " -> "; //gorsellik icin.
                pYazici = pYazici -> pOnceki;   //bir onceki elemana geciyoruz.
            }
            cout << "\n^\nson eklenen eleman.\n";    //gorsellik icin.
        }
        int getElemanSayisi(){ return elemanSayisi;}
};

void kuyrukUygulamasi(bool &donguDevam, queue &kuyruk){
    system("cls");
    cout << "    kuyruk Uygulamasi" << endl;
    cout << "1-> kuyruga eleman ekle\n2-> kuyruktan eleman cikar\n";
    cout << "3-> kuyrugu temizle\n4-> kuyruktaki elemanlari goster\n";
    cout << "5-> kuyruktaki eleman sayisini goster\n6-> ana menuye don\n";
    cout << "yapmak istediginiz islem: ";   int girdi;  cin >> girdi;
    system("cls");
    switch (girdi){
        case 1: {
            cout << "eklemek istediginiz elemani girin(tam sayi olmali): ";
            int girdi2; cin >> girdi2;  kuyruk.ekle(girdi2);     //kullanicidan aldigimiz degeri lsiteye ekliyoruz.
            cout << girdi2 << " listeye eklendi.\n";  system("pause");  break;  //onay mesaji verip case i sonlandiriyoruz.
        }
        case 2: {
            if (kuyruk.getElemanSayisi() > 0){
                kuyruk.cikar(); cout << "ilk eklenen eleman kuyruktan cikarildi.\n";    system("pause");
            }
            else{   cout << "kuyruk bos oldugu icin cikarma islemi yapilamiyor..!\n";   system("pause");}
            break;
        }
        case 3: kuyruk.temizle();    cout << "kuyruk temizlendi.\n";   system("pause");  break;
        case 4: {
            if(kuyruk.getElemanSayisi() == 0){  cout << "liste bos..!\n";   system("pause");}   //eleman sayisi 0 ise lsite bos.
            else{   
                kuyruk.yazdirElemanlar();    
                cout << "\nlistede " << kuyruk.getElemanSayisi() << " adet elaman bulunuyor.\n"; 
                system("pause");
            }   break;  //eleman sayisi 0 degilse elemanlari ekrana yazdir.
        }
        case 5: cout << "listede " << kuyruk.getElemanSayisi() << " adet elaman bulunuyor.\n";  system("pause");    break;
        //donguDevam false olursa fonksiyonu icine alan while dongusu kirilmis olacak.
        case 6: donguDevam = false;    break;
        default:    cout << "hatali giris yaptiniz tekrar deneyin..!\n";  system("pause");  break;
    }
}

int main(){

    queue kuyruk;

    bool donguDevam = true;

    while (donguDevam)
        kuyrukUygulamasi(donguDevam,kuyruk);
    
}