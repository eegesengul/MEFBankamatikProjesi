//PROJE1

//PROJE ADI: BANKAMATIK UYGULAMASI
//BANKAMIZIN ADI: MEFBANK
//TAKIM ISMI: MEFteam
//TAKIM UYELERI: 1)MERT OZMEN 2)SABAN EGE SENGUL 3)FATIH YILMAZ


#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>


int dataSifreler[30], dataHesapNo[30], sifre, hesapNo, dongugirme, gondermesayi=0, islem, girissifresi, i, j, k, secim, hesapSorgu=1, cikis=1, giris=1, yatirmaislem, sorgu;
float dataParalar[30], para;
char dataKullanicilar[30][30], isim[15], soyisim[15], girisismi[15], girissoyismi[15];
FILE *kayitlar;

void ana_menu(int i, int index);

void dosyaya_aktar(int index){ //Bu fonksiyonumuz para yatirilip cekildiğinde veya gonderildiğinde degisen verileri oncekileri silerek tekrar dosyaya yazdirir.                               
    kayitlar = fopen("kayitlar.txt", "w");
    for (j=0; j <index-1; j++){
        fprintf(kayitlar, "%s %d %.1f %d\n", dataKullanicilar[j], dataSifreler[j], dataParalar[j], dataHesapNo[j]);
    }
    fclose(kayitlar);
}

void kayit_ol(){ //Bir dosya olusturup kullanicilari kayit eder ve kullaniciya bir hesap numarasi olusturur.
    kayitlar = fopen("kayitlar.txt", "a");
    printf("\n\tKAYIT EKRANI\t\n");
	printf("\nKayit olmak icin isim ve soyisim giriniz. \n");
    scanf("%s %s", &isim, &soyisim);
    strcat(isim, soyisim);
    printf("\nKayit olmak icin 6 haneli bir sifre olusturunuz. \n");
    while (1){
        scanf("%d", &sifre);
        if (sifre >= 100000 && sifre <= 999999){
            break;
        }
        else{
            printf("Lutfen 6 rakam iceren bir sifre giriniz.\n");
        }
    }
    hesapNo=100000+rand();
    strupr(isim);
    fprintf(kayitlar, "%s %d 0.0 %d\n", isim, sifre, hesapNo);
    fclose(kayitlar);
    printf("\nKayit islemi gerceklestiriliyor...\n");
    sleep(3);
    printf("Kayit islemi basariyla gerceklesmistir.\nAna menuye donuluyor...\n\n");
    sleep(2);
    system("CLS");
}

void para_yatirma(int i, int index){ //Para yatirma islemleri bu fonksiyon ile yapilir. Yatirilmazsa ana menuye doner. Yatirilirsa dosya bilgilerini gunceller.
   	system("CLS");
    printf("\n\tPARA YATIRMA ISLEMI\t\n");
    printf("\nNe kadar para yatirmak istiyorsunuz?(5-10.000TL araliginda yatirabilirsiniz)\nAna menuye donmek icin '0'a basiniz\n");
    while (1){
        scanf("%f", &para);
        if (para == 0){
            ana_menu(i, index);
        }
        else if (para >= 5 && para <= 10000){
            dataParalar[i] += para;
            dosyaya_aktar(index);
            printf("\nParaniz basariyla yatirilmistir.\n");
            sleep(1);
            printf("Ana menuye donuluyor...\n\n");
    		sleep(1);
    		system("CLS");
            break;
		}               
        else{
            printf("\nLutfen belirlenen araliklarda bir tutar giriniz.\n");
        }
    }
}

void para_cekme(int i, int index){ /* Cekebilecek parasi varsa ceker yoksa bu fonksiyona girilmez. 
                                      Cekilmek istenen bakiye kullanicinin parasindan cok ise para cekilmez. Para cekilirse dosyaya aktarilir. */
    system("CLS");
    printf("\n\tPARA CEKME ISLEMI\t\n");
	printf("\nNe kadar para cekmek istiyorsunuz?(5-10.000TL araliginda cekebilirsiniz)\nAna menuye donmek icin '9'a basiniz\n");
    while (1){
        scanf("%f", &para);
        if (para == 9){
            para = 0;
            break;
        }
        else if (para >= 5 && para <= 10000){
            if (dataParalar[i] < para){
                printf("Mevcut bakiyenizden yuksek bir para cekme isleminde bulunamazsiniz.\n");
            }
            else{
                dataParalar[i]-=para;
				dosyaya_aktar(index);
                printf("\nPara cekme isleminiz gerceklestirmistir.\n");
            	sleep(1);
            	printf("Ana menuye donuluyor...\n\n");
    			sleep(1);
    			system("CLS");
                break;
            }
        }
        else{
            printf("Lutfen belirlenen araliklarda bir tutar giriniz\n");
        }
    }
}

void para_gonderme(int i, int index){ /*Kayitli kullanicilar kontrol edilir. Kayitli kullanici veya hesapta para yoksa bu fonksiyona girmez. 
                                        Kayitli kullanici ve para varsa hesap numaralari gozukur ve degerler girilerek para gonderilir. Dosyaya aktarilir. */

    system("CLS");
    printf("\n\tPARA GONDERME ISLEMI\t\n");
	if (dataParalar[i] <= 0){
        printf("Bakiyeniz bulunmamaktadir.\n");
        sleep(1);
        ana_menu(i, index);
    }
    dongugirme=1;
    printf("\n");
    for (j=0;j<index-1;j++){

        if (i==j){
        }
        else if (dataKullanicilar[j][0] == '0'){
		}
        else{
            printf("%s %d\n", dataKullanicilar[j], dataHesapNo[j]);
            gondermesayi++;
        }
    }
    
    if (gondermesayi=0){
        printf("Gonderebileceginiz bir hesap bulunmamaktadir...\n");
        sleep(1);
        ana_menu(i, index);
    }
    printf("Hangi hesap numarasina para aktarmak istiyorsunuz?\nAna menuye donmek icin '0'a basiniz\n");
    while (1){
        scanf("%d", &islem);
        if (islem==0){
            dongugirme=0;
            break;
        }
        for (k=0;k<index-1;k++){
            if (dataHesapNo[k] == islem){
                hesapSorgu=1;
           		break; 
            }
        }
        if(hesapSorgu==1){
            break;
        }
        else{
            printf("Hesap bulunamadi.Lutfen tekrar giriniz veya ana menuye donmek icin '9' basiniz\n");
        }
    }
    printf("Ne kadar para gondermek istiyorsunuz?\nCikis yapmak icin 0'a basiniz\n");
    while (dongugirme==1){
        scanf("%f", &para);
        if (para==0){
            break;
        }
        else if (dataParalar[i]<para){
            printf("Yeterli bakiyeniz bulunmamaktadir.Tekrar deneyiniz veya ana menuye donmek icin '0'a basiniz.\n");
        }
        else{
            break;
        }
    }

    for (j=0;j<index-1;j++){

        if (islem==dataHesapNo[j]){
            dataParalar[j] +=para;
            dataParalar[i] -=para;
            dosyaya_aktar(index);
            printf("Paraniz gonderiliyor.Lutfen bekleyiniz.\n");
            sleep(2);
            printf("Para transferiniz basariyla gerceklestirilmistir.\n\n");
            sleep(1);
            system("CLS");
            break;
        }
    }
}

void ana_menu(int i, int index){ // Yapilmak istenen islem sorulur. Bir fonksiyondan cikilmak istenince donulecek ana menumuz bu fonksiyondur.
    printf("Ana menuye donuluyor...\n\n");
    sleep(1);
    dosyaya_aktar(index);
    system("CLS");
    while (1){
        printf("Sayin %s\n\n", dataKullanicilar[i]);
		printf("Mevcut Bakiyeniz: %.1fTL\n", dataParalar[i]);
    
        printf("Lutfen Yapmak istediginiz islemi seciniz\n1.Para Yatirma\n2.Para Cekme\n3.Para Gonderme\n4.Cikis\n");
        scanf("%d", &islem);
        system("CLS");
        if (islem == 1){
 	       para_yatirma(i, index);
        }
        else if(islem == 2){
        	
			if (dataParalar[i] <= 0){
                        printf("\n\tPARA YATIRMA ISLEMI\t\n");
						printf("Bu islemi gerceklestirmek icin yeterli bakiyeniz bulunmamaktadir.\n");
                        sleep(1);
                        printf("Hesaba para yatirmak ister miydiniz?\n1.Evet\n2.Hayir\n");
                        while (1){
                            scanf("%d", &yatirmaislem);
                            if (yatirmaislem == 1){
                                printf("Para yatirma islemine yonlendiriliyorsunuz...\n");
                                sleep(1);
                                para_yatirma(i, index);
                            }
                            else if (yatirmaislem == 2){
                            	system("CLS");
                                break;
                            }
                            else{
                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                            }
                        }
		    }
            else{
                para_cekme(i, index);
            }
    }
        else if (islem == 3){
            para_gonderme(i, index);
            break;
        }
        else if (islem == 4){
            printf("\n\t\t\tMEFBANK\n\tBizi tercih ettiginiz icin tesekkurler.\n\t\tIyi Gunler Dileriz...\n");
            sleep(1);
            system("CLS");
            break;
        }
        else{
            printf("Lutfen gecerli bir tuslama yapiniz.\n\n");
        }
    }
}

void kayit_sil(){ // Silinebilecek hesaplari dosyadan tarar. Eger varsa bilgileri ister. Bilgiler dosyadakiler ile uyusursa kullanicinin butun bilgilerini sıfırlar.
    int index = 0;
    hesapSorgu=1;
    if((kayitlar=fopen("kayitlar.txt", "r")) != NULL){
        kayitlar = fopen("kayitlar.txt", "r");
        while (!feof(kayitlar)){
            fscanf(kayitlar, "%s %d %f %d", &dataKullanicilar[index], &dataSifreler[index], &dataParalar[index], &dataHesapNo[index]);
            index++;
        }
        printf("\n\tKAYIT SILME EKRANI\t\n");
		printf("Silmek istediginiz hesabin ismini ve soyismini giriniz:\n");
        scanf("%s%s", &girisismi, &girissoyismi);
        printf("Silmek istediginiz hesabin sifresini giriniz\n");
        scanf("%d", &girissifresi);
        strcat(girisismi, girissoyismi);
        strupr(girisismi);
        for (i=0;i<index-1;i++){
            if ((strcmp(girisismi, dataKullanicilar[i]) == 0) && girissifresi == dataSifreler[i]){
                k = strlen(dataKullanicilar[i]);
                for (j=0;j<k;j++){
                    dataKullanicilar[i][j] = '0';
                }
                dataSifreler[i] = 0;
                dataHesapNo[i] = 0;
                dataParalar[i] = 0;
                hesapSorgu=0;
                dosyaya_aktar(index);
                printf("Silme islemi gerceklestirilmistir.\nAna menuye donuluyor...\n\n");
                sleep(2);
                system("CLS");
                main();
            }
        }
        if (hesapSorgu==1){
            printf("Boyle bir hesap bulunamadi!\n1.Tekrar Dene\n2.Ana Menuye Don\n");
            while (1){
                scanf("%d", &islem);
                system("CLS");
                if (islem == 1){
                    kayit_sil();
                }
                else if (islem == 2){
                    printf("Ana menuye donuluyor...\n\n");
					system("CLS");
                    sleep(1);
                    main();
                }
                else{
                    printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                }
            }
        }
    }
    else{
        printf("Silinecek herhangi bir hesap bulunmamaktadir.\n\n");
        sleep(1);
        main();
    }
}

void giris_yap(){ //Kayitli kullanici varsa dosyadan tarayarak uyusuyor mu diye kontrol eder. Uyusursa giris yapilir ve yapilmak istenen islemler icin secim sunar.
    int index = 0;
    if ((kayitlar = fopen("kayitlar.txt", "r")) != NULL){
        kayitlar = fopen("kayitlar.txt", "r");
        while (!feof(kayitlar)){
            fscanf(kayitlar, "%s %d %f %d", &dataKullanicilar[index], &dataSifreler[index], &dataParalar[index], &dataHesapNo[index]);
            index++;
        }
        do{
            printf("\n\tGIRIS EKRANI\t\n");
			printf("\nIsminizi ve soyisminizi giriniz:\n");
            scanf("%s%s", &girisismi, &girissoyismi);
            printf("Sifrenizi giriniz:\n");
            scanf("%d", &girissifresi);
            strcat(girisismi, girissoyismi);
            strupr(girisismi);
            strupr(girissoyismi);
            printf("\nGiris islemi gerceklestiriliyor...\n");
    		sleep(2);
    		sorgu=1;
            for (i=0;i<index-1;i++){
            
				if ((strcmp(girisismi, dataKullanicilar[i]) == 0) && girissifresi == dataSifreler[i]){
                    
					printf("Giris Onaylandi\n\n");
					sleep(1);
					system("CLS");
					printf("HOSGELDINIZ...\n");
                    hesapSorgu=0;
                    sorgu=0;
                    giris=1;
                    
                    while (giris){
        printf("Sayin %s\n\n", dataKullanicilar[i]);            	
        printf("Mevcut Bakiyeniz: %.1fTL\n", dataParalar[i]);
    
        printf("Lutfen Yapmak istediginiz islemi seciniz\n1.Para Yatirma\n2.Para Cekme\n3.Para Gonderme\n4.Cikis\n\n");
        scanf("%d", &islem);
        system("CLS");
        if (islem == 1){
 	       para_yatirma(i, index);
        }
        else if(islem == 2){
        	
			if (dataParalar[i] <= 0){
                        printf("\n\tPARA CEKME ISLEMI\t\n");
						printf("Bu islemi gerceklestirmek icin yeterli bakiyeniz bulunmamaktadir.\n");
                        sleep(1);
                        printf("Hesaba para yatirmak ister miydiniz?\n1.Evet\n2.Hayir\n");
                        while (1){
                            scanf("%d", &yatirmaislem);
                            if (yatirmaislem == 1){
                                printf("Para yatirma islemine yonlendiriliyorsunuz...\n");
                                sleep(1);
                                para_yatirma(i, index);
                                break;
                            }
                            else if (yatirmaislem == 2){
                            	system("CLS");
                                break;
                            }
                            else{
                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                            }
                        }
					}
                    else{
                        para_cekme(i, index);
                    }
                }
        else if (islem == 3){
            para_gonderme(i, index);
        }
        else if (islem == 4){
            printf("\n\t\t\tMEFBANK\n\tBizi tercih ettiginiz icin tesekkurler.\n\t\tIyi Gunler Dileriz...\n");
            sleep(1);
            system("CLS");
            giris=giris-1;
            break;
        }
        else{
            printf("Lutfen gecerli bir tuslama yapiniz.\n\n");
       					 }
   					 }	
                }
            }

            if (sorgu==1){
                printf("Boyle bir banka hesabi bulunamadi\n0.Ana Menuye Don\n1.Tekrar Dene\n");
                while (1){
                    scanf("%d", &secim);
                    system("CLS");
                    if (secim == 0){
                        printf("Ana menuye donuluyor...\n\n");
                        sleep(1);
                        system("CLS");
                        main();
                    }
                    else if (secim == 1){
                        break;
                    }
                    else{
                        printf("Lutfen belirtilen araliklarda secim yapiniz\n");
                    }
                }
            }
        } while (sorgu==1);
        fclose(kayitlar);
    }
    else{
        printf("Lutfen oncelikle kayit olunuz.\n\n");
        sleep(1);
        main();
    }
}

int main(){
    srand(time(NULL));
    while(cikis){
    	printf("MEFBANK'a Hosgeldiniz!\nSize Nasil Yardimci Olabiliriz?\n\n");
        printf("1.Kayit Ol\n2.Giris Yap\n3.Kayit Sil\n4.Cikis Yap\n\n");
        scanf("%d", &islem);
        system("CLS");
        switch(islem){
        	case 1: kayit_ol();
        			break;
        	case 2: giris_yap();
        			break;
    		case 3: kayit_sil();
        			break;
        	case 4: printf("\n\t\t\tMEFBANK\n\tBizi tercih ettiginiz icin tesekkurler.\n\t\tIyi Gunler Dileriz...\n");	
        			cikis=cikis-1;
        			break;
        	default: printf("Lutfen gecerli bir tuslama yapiniz.\n\n");
						
		}
    }
    return 0;
}
