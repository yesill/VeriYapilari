#include <iostream>
using namespace std;

class treeNode{
    public:
    int veri;   //dugumun girilen sayiyi tutan kismi
    treeNode *sol;  //sol pointer
    treeNode *sag;  //sag pointer
};

class binaryTree{
    int elemanSayisi;
    public:
        treeNode *kok;
        treeNode *avare;  //gezinmek icin kullandigimiz pointer imiz.

        binaryTree(){
            elemanSayisi = 0;   //yeni bir agac olusturdugumuzda eleman sayisi 0 olacak.
        }

        void ekle(int deger){
            treeNode *nodeTemp = new treeNode();    //bos bir dugum olusturuyoruz.
            nodeTemp -> veri = deger;   //girilen degeri bos dugumun icerisine atip bekletiyoruz
            //dugum olusturuldu agacta koymak istedigimiz yeri bulup hazir olan dugumu point edecegiz.

            //agaca ilk elemani eklerken
            if (elemanSayisi == 0){
                kok = nodeTemp;
                elemanSayisi++;
                cout << deger << " agaca eklendi..!" << endl;
            }

            //eklenecek eleman agacin ilk elemani degilse
            else{
                avare = kok;  //burada avare = kok yani en basa donduk.
                
                //istenilen yere ulasilana kadar sonsuz dongu.
                while(true){

                    //son dugumun verisi yeni girdigimiz veriden kucuk ise(sol)
                    if (nodeTemp -> veri < avare -> veri){
                        
                        //son dugumun sol pointer bolumu bir dugumu point etmiyorsa.
                        if (avare -> sol == NULL){
                            avare -> sol = nodeTemp;  //yeni dugumumuz bos olan yere koyuldu.
                            cout << deger << " agaca eklendi..!" << endl;
                            break;  //dongu sonlandirildi.
                        }
                        
                        //son dugumun sol pointer bolumu hali hazirda bir dugumu point ediyorsa, point etmeyene kadar dongu devam etmeli.
                        else{
                            avare = avare -> sol;
                            continue;
                        }
                    }

                    //son dugumun verisi yeni girdigimiz veriye esit veya buyuk ise(sag) 
                    else if (nodeTemp -> veri > avare -> veri){

                        //sag pointer bos ise yeni dugumu oraya yerlestirebiliriz.
                        if (avare -> sag == NULL){
                            avare -> sag = nodeTemp;
                            cout << deger << " agaca eklendi..!" << endl;
                            break;
                        }

                        //sag dugum bos olana kadar dongu devam etmeli.
                        else{
                            avare = avare -> sag;
                            continue;
                        }
                    }

                    //eklenmek istenen deger zaten varsa
                    else{
                        cout << "eklenmek istenen deger agacta mevcut..!" << endl;
                        elemanSayisi--;
                        break;
                    }
                }

                elemanSayisi++; //ekleme islemi gerceklesti eleman sayisi arttiriliyor.
            }
        }

        void cikar(int deger){
            avare = kok;  //agacin en tepesine cikmis oluyoruz.
            //avareyi takip edecek bir pointer. cikaracagimiz dugumun bir ustunu ve bir altini birlestirmemiz gerek.
            treeNode *takipci = avare;  //baslangic degeri avareye esit.
            bool enSonGirilenYonSoldu = NULL;   //kokun solundan devam ediyorsak true.
            //istenilen degere ulasilana kadar sonsuz dongu
            while(true){

                //girilen deger kokten kucuk ise soldan devam ediyoruz.
                if(deger < avare -> veri){
                    takipci = avare;    //takipci bir dugum geriden geliyor.
                    avare = avare -> sol;   //avare soldan devam ediyor.
                    continue;
                }

                //girilen deger kokten buyuk ise sagdan devam ediyoruz.
                else if (deger > avare -> veri){
                    takipci = avare;    //takipci bir dugum geriden geliyor
                    avare = avare -> sag;   //avare sagdan devam ediyor.
                    continue;
                }

                //girilen deger kokteki veriye esit ise cikarma islemini gerceklestiriyoruz.                
                else{
                    //girilen deger agacta yoksa
                    if(avare -> veri != deger){
                        cout << "cikartilmak istenen deger bulunamadi..!" << endl;
                        break;
                    }
                    
                    //girilen deger agacta varsa
                    else{
                        treeNode *beklemeOdasi = new treeNode();  //bagi koparilan dugumun yeni yeri bulunana kadar bekletildigi pointer
                        
                        //2 cocuk varsa, sagdaki kokun yerine gecer ve soldaki veriler uygun yere konur(assagida aciklandi.)
                        if(avare -> sag != NULL && avare -> sol != NULL){
                            beklemeOdasi = avare -> sol;    //soldaki dugum/dugumler uygun yer bulunana kadar bekletiliyor.
                            avare = avare -> sag;   //2. cocuk var sa oncelik buyuk olanda yani sagda. sag taraftan bir adim ilerliyoruz.
                            
                            //gidilen tarafa gore kokuteki pointeri dugume bagliyoruz.
                            if(enSonGirilenYonSoldu)
                                takipci -> sol = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.
                            else
                                takipci -> sag = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.

                            //bekleme odasina alinan soldaki dugum/dugumler yeni kokun en solundaki dugumden bile kucuk olacaklari icin,
                            //yeni kokten sola dogru dugumler bitene kadar ilerliyoruz.
                            while(true){
                                //solda dugum kalmadiginda bekleme odasindaki dugum/dugumleri buraya koyuyoruz.
                                if(avare -> sol == NULL){
                                    avare -> sol = beklemeOdasi;
                                    break;
                                }
                                //solda dugum kalmayana kadar ilerliyoruz.
                                else{
                                    avare = avare -> sol;
                                }
                            }

                        }
                        
                        //sagda cocuk var ama solda yok ise
                        else if(avare -> sag != NULL && avare -> sol == NULL){
                            avare = avare -> sag;   //silinecek kokun bir sagindaki cocugu aliyoruz
                            
                            //gidilen tarafa gore kokuteki pointeri dugume bagliyoruz.
                            if(enSonGirilenYonSoldu)
                                takipci -> sol = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.
                            else
                                takipci -> sag = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.                        
                        }
                        
                        //solda cocuk var ama sagda cocuk yok ise
                        else if(avare -> sag == NULL && avare -> sol != NULL){
                            avare = avare -> sol;
                            takipci -> sol = avare;

                            //gidilen tarafa gore kokuteki pointeri dugume bagliyoruz.
                            if(enSonGirilenYonSoldu)
                                takipci -> sol = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.
                            else
                                takipci -> sag = avare; //takipci silinecek kokun bir adim gerisinde avare bir adim ilerisinde. iksini bagliyoruz.
                        }
                        
                        //cocuk yok ise
                        else{
                            //gidilen tarafa gore kokuteki pointeri dugume bagliyoruz.
                            if(enSonGirilenYonSoldu)
                                takipci -> sol = NULL;  
                            else
                                takipci -> sag = NULL;
                        
                        }

                        elemanSayisi--;
                        break;
                    }
                }
            }
        }

        void inOrder(treeNode *node){
            if(node){
                inOrder(node -> sol);
                cout << node -> veri << endl;
                inOrder(node -> sag);
            }
        }

        void preOrder(treeNode *node){
            if(node){
                cout << node -> veri << endl;
                preOrder(node -> sol);
                preOrder(node -> sag);
            }
        }

        void postOrder(treeNode *node){
            if(node){
                postOrder(node -> sol);
                postOrder(node -> sag);
                cout << node -> veri << endl;
            }
        }

        void temizle(){ kok = NULL; avare = NULL;   elemanSayisi = 0;}

        int getElemanSayisi(){ return elemanSayisi;}

};

void agacUygulamasi(bool &donguDevam, binaryTree &agac){
    system("cls");
    cout << "    Agac Uygulamasi" << endl;
    cout << "1-> agaca eleman ekle\n2-> agactan eleman cikar\n";
    cout << "3-> agaci temizle\n4-> agactaki eleman sayisini goster\n";
    cout << "5-> agaci InOrder dolasarak elemanlari goster\n";
    cout << "6-> agaci PreOrder dolasarak elemanlari goster\n";
    cout << "7-> agaci PostOrder dolasarak elemanlari goster\n";
    cout << "8-> ana menuye don\n";
    cout << "yapmak istediginiz islem: ";   int girdi;  cin >> girdi;
    system("cls");
    switch (girdi){
        case 1:
            cout << "agaca eklemek istediginiz tam sayiyi girin: ";
            int girdi2; cin >> girdi2;  agac.ekle(girdi2);  //kullanicidan aldigimiz degeri lsiteye ekliyoruz.
            system("pause");    break;
        case 2:
            if (agac.getElemanSayisi() == 0)    cout << "agac bos..! cikarma istelemi yapilamiyor\n";
            else{
                cout << "cikarmak istediginiz deger: ";
                int girdi2; cin >> girdi2;  agac.cikar(girdi2); //girilen degeri cikariyoruz.
            }
            system("pause");    break;
        case 3: agac.temizle(); cout << "agac temizlendi..!\n"; system("pause");    break;
        case 4:
            if (agac.getElemanSayisi() == 0){   cout << "agac bos\n";   system("pause");    break;}
            else{   cout << "agacta " << agac.getElemanSayisi() << " adet eleman bulunuyor.\n";}
            system("pause");
            break;
        case 5: agac.inOrder(agac.kok); system("pause");    break;
        case 6: agac.preOrder(agac.kok);    system("pause");    break;
        case 7: agac.postOrder(agac.kok);   system("pause");    break;
        case 8: donguDevam = false;    break;
        default:    cout << "hatali giris yaptiniz tekrar deneyin..!\n";  system("pause");  break;
    }
}

int main(){

    binaryTree agac;

    bool donguDevam = true;

    while (donguDevam)
        agacUygulamasi(donguDevam,agac);
    
}