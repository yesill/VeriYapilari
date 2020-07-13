#include <iostream>
using namespace std;


class node{
    public:
        int veri;       //dugumun girilen veriyi tutan kismi.
        node *pOnceki;  //onceki eleman mantigini tercih ettim.
};

class stack{
    int elemanSayisi;   //yigin icerisindeki eleman sayisi
    node *pTemp;    //bir nevi "top" deger gibi, asagida ayrintili acikladim.
    /*  
        pTemp in amaci ve ekleme fonksiyonunu asagida acikladim;
        Stacke bir item ekleyelim ismi "A" olsun. "A" ilk eleman oldugu icin adres kismi bos(pOnceki), "A" nin adresi
        ise pTemp e kaydediliyor(son eklenen eleman). Sonra Stacke ikinci bir eleman daha ekleyelim ismi "B" olsun. 
        Bu sefer "B" den once gelen bir eleman var, bu sebeple B -> pOnceki = "A nin adresi" olmali. "A" nin adresini 
        pTemp e kaydettigimiz icin, B -> pOnceki = pTemp olmali.
        En ustteki(top) itemin adresi pTemp te bulunuyor.
    */
    public:
        stack(){    
            elemanSayisi = 0;   //yeni stack bos olmali.
            pTemp = NULL;   //ilk elemanin oncesinde point edecek birsey olmadigi icin NULL.
        }
        void ekle(int deger){   //ekleme fonksiyonunu yukarida anlattim. 
            node *n = new node; //yeni dugum olusturuyoruz.
            n -> veri = deger;  //girilen degeri dugumdeki veriye esitliyor.
            n -> pOnceki = pTemp;   //pTemp(top), n bunun uzerine ekleniyor. pOnceki top u gostermeli.
            pTemp = n;  //pTemp en son eklenen elemani(n) gosteriyor.(top)
            elemanSayisi++; //ekleme islemi oldugu icin eleman sayimizi arttiriyoruz.
        }
        //pTemp(top) i bir onceki nodu gosterecek sekilde degistiriyoruz.
        void cikar(){   pTemp = pTemp -> pOnceki;   elemanSayisi--;}
        //son eklenen elemani null yaparsak liste temizlenmis olur, sondan basa gidiyoruz ve "son" artik yok.
        void temizle(){ pTemp = NULL;   elemanSayisi = 0;}
        void yazdirElemanlar(){
            node *pYazici = pTemp;  //pTemp in degismemesi icin.
            if (elemanSayisi == 0)    cout << "yiginda eleman yok..!\n";
            else{
                int sayac = 0;   //gorsellik icin.
                while(pYazici != NULL){
                    cout << pYazici -> veri;    //mevcut elemanin icindeki veriyi yazidiriyoruz.
                    sayac++;    //gorsellik icin.
                    if (sayac < elemanSayisi)  cout << " -> "; //gorsellik icin.
                    pYazici = pYazici -> pOnceki;   //mevcut dugumden bir ondeki dugume gidiyor.
                }
                cout << "\n^\nson eklenen eleman.\n";    //gorsellik icin.
            }
        }
        int getElemanSayisi(){ return elemanSayisi;}
};

void yiginUygulamasi(bool &donguDevam, stack &yigin){
    system("cls");
    cout << "    yigin Uygulamasi" << endl;
    cout << "1-> yigina eleman ekle\n2-> yigindan eleman cikar\n";
    cout << "3-> yigini temizle\n4-> yigindanki elemanlari goster\n";
    cout << "5-> yigindaki eleman sayisini goster\n6-> cikis yap\n";
    cout << "yapmak istediginiz islem: ";   int girdi;  cin >> girdi;   //kullanicidan yapmak istedigi islemin kodunu aliyoruz.
    system("cls");  //cmd ekranini temizliyoruz.
    switch(girdi){
        case 1: {
            cout << "eklemek istediginiz elemani girin(tam sayi olmali): ";
            int girdi2; cin >> girdi2;  yigin.ekle(girdi2);     //kullanicidan aldigimiz degeri lsiteye ekliyoruz.
            cout << girdi2 << " listeye eklendi.\n";    //onay mesaji.
            system("pause");    //klavyeden herhangi bir giris yapilana kadar sonraki satira gecmiyor.
            break;
        }
        case 2: {   
            if(yigin.getElemanSayisi() > 0){
                yigin.cikar();  cout << "son eklenen eleman listeden cikarildi.\n";     system("pause");
            }
            else{   cout << "yigin bos oldugu icin cikarma islemi yapilamiyor..!" << endl;  system("pause");}
            break;
        }
        case 3: yigin.temizle();    cout << "yigin temizlendi.\n";    system("pause");  break;
        case 4: {
            if(yigin.getElemanSayisi() == 0){   cout << "liste bos..!\n";   system("pause");}   //eleman sayisi 0 ise lsite bos.
            else{   
                yigin.yazdirElemanlar();    
                cout << "\nlistede " << yigin.getElemanSayisi() << " adet elaman bulunuyor.\n"; 
                system("pause");
            }   break;  //eleman sayisi 0 degilse elemanlari ekrana yazdir.
        }
        case 5: cout << "listede " << yigin.getElemanSayisi() << " adet elaman bulunuyor.\n"; system("pause");  break;
        //donguDevam false olursa fonksiyonu icine alan while dongusu kirilmis olacak.
        case 6: cout << "cikis yapildi\n";    donguDevam = false;    break;
        default:    cout << "hatali giris yaptiniz tekrar deneyin..!\n";  system("pause");  break;
    }
}

int main(){

    stack yigin;

    bool donguDevam = true;

    while (donguDevam)
        yiginUygulamasi(donguDevam,yigin);
    
}