#include <cstdlib>
#include <iostream>
#include <conio.h>
//#include <fstream>
#include <string.h>
#include <stack>
#include <cmath>
using namespace std;
const double PI=3.141593;  //pý sabitimizi tanýmladýk
const double E=2.718281;   //e sayýsý sabitimizi tanýmladýk
struct eleman{             //eleman  adýnda yapýmýzý tanýmladýk
	char icerik[50];       //icerik adýnda deðiþkenimizi tanýmladýk
	struct eleman *ileri;  //baðlý listemiz çift ynlü oldugu için ileri 
	struct eleman *geri;   //ve geri pointer tanýmlamalarýný yaptýk
};
typedef struct eleman Eleman;  //yapýmýzý  adlandýrdýk
typedef Eleman* Elemanptr;     // adlandýrdýðýmýz yapýya pointer atadýk
struct liste{                
	Elemanptr bas;             //Eleman  türün de listemizi oluþturduk 
	Elemanptr son;
};
typedef struct liste Liste;   //listemizi adlandýrdýk
typedef Liste* Listeptr;      //listemize  pointer atadýk caðýrmamýz için

Listeptr yeni_liste ()       //Listeptr türünde yeni liste oluþturduk
{ 
	Listeptr liste ;         //liste olarak adlandýrdýk
	liste = (Listeptr)malloc(sizeof(Liste));   //listeye Listeptr türüne göre alan tahsis ettik
	liste ->bas = NULL;      //ilk olarak listenin basýný bos olarak tanýmladýk
	liste ->son = NULL;      //ilk olarak listenin sonunu bos olarak tanýmladýk
	return liste ;           //listemizi döndürdük
}

void veri_ekle(char veri[],Listeptr l) //temp->veriye ve liste->l'ye buraya atanýr
{
	if(l->bas==NULL){  //listemizin basý bos ise
		Elemanptr yeni;  //elemanptr türünde yeni tanýtacak
		yeni=(Elemanptr)malloc(sizeof(Eleman)); //yeni degiskenine elemanptr türünde alan tahsisi olacak
		strcpy(yeni->icerik,veri); //veri yeninin içeriðine atanýr
		yeni->geri=NULL;  //yeninin gerisi bos olur
		yeni->ileri=NULL; //yeninin ilerisi bos olur
		l->bas=yeni;      //yeniyi listenin basýna eklenilir 
		l->son=yeni;      //yeniyi listenin sonuna ekler
	}	else{     //liste bos degilse
		Elemanptr temp=(Elemanptr)malloc(sizeof(Eleman));//elemanptr türünde temp'e alan tahsis edilir
		strcpy(temp->icerik,veri);//veri tempteki icerige atanýr
		temp->ileri=NULL;//temp'in ilerisi bos olarak olusturulur
		temp->geri=l->son; //listenin sonunu temp'in gerisine atar
		l->son->ileri=temp;//listenin sonunun ilerisine temp'i atar
		l->son=temp;//listenin sonu temp olur
		}
}

void denklem_ekle(char veri[],Listeptr l,int j) //temp ,liste ve j degiskeni buraya atandý diger sarrtta j+1 gönderecek
{
	char temp[50];  //temp dizisi tanýttýk
	for(int i=0;i<j;i++) temp[i]=veri[i]; //i ve j'ye göre for oluþturup verideki degerleri tempe atacak
	for(int i=j;i<50;i++) temp[i]=0;   //for a göre tempin degerlerini sýfýra esitleyecek
	veri_ekle(temp,l);     //temp ve listeyi veri_ekle fonksiyonuna gönderir
	
}

void listeye_ekle(Elemanptr eleman,Listeptr liste)  //temp ve yeni listeyi atadýk buraya
{
	if(liste->bas==NULL)  //listenin basý bos ise
	{ 
		eleman->geri=NULL;    //tempin gerisine bos olsun
		liste->bas=eleman;    //listenin basý eleman olsun
	}
	else  //degilse
	{
		liste->son->ileri=eleman; //liste sonunun ilerisine elemaný ekle
		eleman->geri=liste->son; //listenin sonunuda elemanýn gerisine ekle
	}                          //böylece elemaný sona eklemiþ oluruz
	eleman->ileri=NULL;//elemanýn ilerisini bos olarak tanýmla
	liste->son=eleman;  //listenin sonuna elemaný ata
}

void listele(Listeptr l)   //gelen liste l  adýndaki listeye atanýr
{
	Elemanptr temp=l->bas;   //listenin basý elemanptr türündeki tempe atanýr
	cout<<endl;              //yazma iþleminde görevli olacaktýr.
	while(temp!=NULL){       //temp bos olmadýgý müddetce
		cout<<temp->icerik;  //tempin iceriði yazdýrýlýr
		temp=temp->ileri;    //daha sonra tempin ilerisi tempe atanýr böylece hepsi yazdýrýlýr
	}
}

int krk_knt(char dizi[])   //tanýmladýðýmýz fonksiyona denklemi diziye atadýk
{
	int i=0;  //i'yi tanýmladýk
	while(i<strlen(dizi)) //dizinin karakter uzunluðu i'den büyük oldugu muddetce
	{
		if(dizi[i]>=40&&dizi[i]<=57&&dizi[i]!=44) i++; //ascii karakter sorgulanmasý yapýlýyor
		else if(dizi[i]=='{'||dizi[i]=='}'||dizi[i]=='['||dizi[i]==']'||dizi[i]=='!'||dizi[i]=='%'||dizi[i]=='^') i++; //karakter sorgusuna göre arttýrma
		else if(dizi[i]=='e'&&dizi[i+1]=='x'&&dizi[i+2]=='p') i+=3;//exp sayýsýný sorguladýk ona göre arttýrým yaptýk
		else if(dizi[i]=='p'&&dizi[i+1]=='i') i+=2; //pi karakteri için sorgulama yaptýk
		else if(dizi[i]=='P'&&dizi[i+1]=='I') i+=2; //PI karakteri için sorgulama yaptýk
		else if(dizi[i]=='l'&&dizi[i+1]=='n') i+=2; //ln karakteri için sorgulama yaptýk
		else if(dizi[i]=='l'&&dizi[i+1]=='o'&&dizi[i+2]=='g') i+=3; //log karakteri için sorgulama yaptýk 
		else if(dizi[i]=='t'&&dizi[i+1]=='a'&&dizi[i+2]=='n') i+=3; //tan karakteri için sorguladýk
		else if(dizi[i]=='s')//sin ve sgn karakteri için sorgu
		{
			if(dizi[i+1]=='i'&&dizi[i+2]=='n') i+=3; //sin için sorgu
			else if(dizi[i+1]=='g'&&dizi[i+2]=='n') i+=3;//sgn için sorgu
			else return i;
		}
		else if(dizi[i]=='c') //cos ve cot karakteri için sorgu
		{
			if(dizi[i+1]=='o'&&dizi[i+2]=='s') i+=3; //cos için sorgu
			else if(dizi[i+1]=='o'&&dizi[i+2]=='t') i+=3;//cot için sorgu
			else return i;//hiçbiri ise i döndür
		}
		else if(dizi[i]=='a')  //asin,atan,acos,acot için sorgu
		{
			if(dizi[i+1]=='s'&&dizi[i+2]=='i'&&dizi[i+3]=='n') i+=4; //asin icin karakter sorgusu
			else if(dizi[i+1]=='t'&&dizi[i+2]=='a'&&dizi[i+3]=='n') i+=4;//atan icin karakter sorgu
			else if(dizi[i+1]=='c')  //acos ve acot'un cos ve cot kýsmý sorgusu
			{
				if(dizi[i+2]=='o'&&dizi[i+3]=='s') i+=4; //acos karakter sorgusu
				else if(dizi[i+2]=='o'&&dizi[i+3]=='t') i+=4;//acot karakter sorgusu
				else return i;//hiçbiri ise i döndür
			}
			else return i;//hiçbiri ise i döndür
		}
		else return i;//hiçbiri ise i döndür
	}
return -1;	//yukarýdakiler olmaz ise -1 döndür
	
}

void bagli_yapma(char denklem[],Listeptr liste) //denkelem ve liste buraya atandý
{
	
	char temp[50]; //temp tanýtýmý yapýldý
	char bos[50]; //bosumuzun tanýtýmý yapýldý
	int j=0;	  //j degikeni tanýtýldý
	for(int i=0;i<strlen(denklem);i++) //i degerimizi denklemin uzunluguna kadar döngüyü soktuk
	{
		if(denklem[i]!='('&&denklem[i]!=')'&&denklem[i]!='{'&&denklem[i]!='}'&&denklem[i]!='['&&denklem[i]!=']'&&denklem[i]!='/'&&denklem[i]!='*'&&denklem[i]!='+'&&denklem[i]!='-'&&denklem[i]!='^'&&denklem[i]!='%'&&denklem[i]!='!')
		{ //denklemde yukarýdaki semboller kullanýlmadýysa degerleri temp dizimize atadýk 
			temp[j]=denklem[i];
			j++;    //j'yi bir arttýrýr
		}
		else //kullanýldýysa
		{	
			if(j!=0) //ve j sýfýrdan farklýysa
			{
				denklem_ekle(temp,liste,j);  //denklem_ekle fonksiyonuna temp liste ve j yi gönderir
				j=0;  //j'yi daha sonra sýfýra esitler
			}                                                                                                    //sinana sor bakalým:)
			temp[j]=denklem[i]; //denklemdeki deðiþkenleri temp dizisine atacak
			denklem_ekle(temp,liste,j+1);  //burda ise j'yi 1 arttýrýp denklem_ekle fonksiyonuna gönderecek
			j=0;
		}
	}
	if(j!=0)//j sýfýrdan farklý olacak sekilde 
	{
		denklem_ekle(temp,liste,j);//denklem ekleye gönderilir                                       //sinana sor bakalým:)
		j=0;
	}
}

int hata(Listeptr liste)   //listemizi listeye atadýk
{
	int sayi=0;    //degisken tanýtýmý yapýldý
	stack <char> s;  //char türünde s adýnda stack tanýtýmý yapýldý
	s.push(0);       //stack e 0 degeri atandý
	Elemanptr temp=liste->bas;   //listenin basýný elemanptr türündeki tempe atadýk
	while(temp!=NULL)     //temp bos olmadýgý müddetce
	{
		if(temp->icerik[0]=='(' || temp->icerik[0]=='{' || temp->icerik[0]=='[')//tempin içeriðininilk karakteri (,{,[ ise
		{
			if(temp->ileri!=NULL) //tempin ilerisi bos deðilse
			{ 
				if(temp->ileri->icerik[0]=='*' || temp->ileri->icerik[0]=='/' || temp->ileri->icerik[0]=='+' || temp->ileri->icerik[0]=='-' || temp->ileri->icerik[0]=='^' || temp->ileri->icerik[0]=='%')
				{//tempin ilerisinin iceriðinde yukarýdaki sart sembollerinden birini saðlarsa
					cout<<sayi+2<<". yerde isaret hatasi var.";  //yazdýr
					return 1;  //1 degerini döndür
				}
				else if(temp->ileri->icerik[0]==')' || temp->ileri->icerik[0]=='}' || temp->ileri->icerik[0]==']')
				{//degilse ve ) veya} veya ] ise
					cout<<sayi+1<<". ve "<<sayi+2<<". yerdeki parantezlerde hata var.";  //yazdýr
					return 1;	//1 degeri döndür
				}
			}
			if(temp->geri!=NULL)
			{
				//if(temp->geri->icerik[0]!='*' && temp->geri->icerik[0]!='/' && temp->geri->icerik[0]!='+' && temp->geri->icerik[0]!='-' && temp->geri->icerik[0]!='^' && temp->geri->icerik[0]!='%' && temp->geri->icerik[0]!='(' && temp->geri->icerik[0]!='{' && temp->geri->icerik[0]!='[')
				if(temp->geri->icerik[0]>=48&&temp->geri->icerik[0]<=57)//ascýý kodlamaya göre karsýlastýrma saðlýyor ise
				{
					cout<<sayi<<". yerden sonra isaret konmasi gerek.";   //yazdýr
					return 1;//1 degeri döndür
				}
			}
			s.push(temp->icerik[0]);   //tempin içeriginin ilk degerini stacke ekle
		}
		else if(temp->icerik[0]==')' || temp->icerik[0]=='}' || temp->icerik[0]==']' || temp->icerik[0]=='!')
		{  //yukarýdakiler degilse eger ) veya} veya] veya ! ise
			if(temp->geri!=NULL)  //tempin gerisi bos degilse
			{
				if(temp->geri->icerik[0]=='*' || temp->geri->icerik[0]=='/' || temp->geri->icerik[0]=='+' || temp->geri->icerik[0]=='-' || temp->geri->icerik[0]=='^' || temp->geri->icerik[0]=='%')
				{//tempin gerisinin iceriginin ilk karakteri sembollerden biri ise
					cout<<sayi<<". yerde isaret hatasi var.";   //yazdýr
					return 1; //1 degerini döndür
				}
			}
			if(temp->ileri!=NULL) //tempin ilerisi bos deðilse
			{ 
				if(temp->ileri->icerik[0]!='*' && temp->ileri->icerik[0]!='/' && temp->ileri->icerik[0]!='+' && temp->ileri->icerik[0]!='-' && temp->ileri->icerik[0]!='^' && temp->ileri->icerik[0]!='%' && temp->ileri->icerik[0]!='!' && temp->ileri->icerik[0]!=')' && temp->ileri->icerik[0]!='}' && temp->ileri->icerik[0]!=']')
				{//tempin ilerisinin içeriði yukarýdaki verden birine eþit ise
					cout<<sayi+1<<". yerden sonra isaret konmasi gerek.";   
					return 1;
				}
			}
			if(temp->icerik[0]==')')
			{  //tempin içeriðinin ilk karakteri ) ise
				char top=s.top(); //stack in baþýndakini topa at
				if(s.top()!='(')  //stackin basý ( farklý ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var."; 
					return 1;
				}
				else s.pop();   //deðilse stackin baþý yap			
			}
			else if(temp->icerik[0]=='}')  
			{//tempin ilk karakteri } ise
				char top=s.top();  //stackin baþýndakini topa at
				if(s.top()!='{')   //stackin baþý { farklý ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var."; 
					return 1;
				}
				else s.pop();  //deðilse stackin basýda ol			
			}
			else if(temp->icerik[0]==']')
			{ //tempin içeriðinin ilk karakteri ] ise
				char top=s.top();//stackin basýndakini topa at
				if(s.top()!='[') //stackin basý [ farklý ise
				{
					cout<<sayi+1<<". yerde parantez hatasi var"; 
					return 1;
				}
				else s.pop();// deðilse stackin basýnda ol	
			}
		}
		if(temp->icerik[0]=='*' || temp->icerik[0]=='/' || temp->icerik[0]=='+' || temp->icerik[0]=='-' || temp->icerik[0]=='^' || temp->icerik[0]=='%')
		{//tempin içeriðinin ilk karakteri yukarýdaki iþaretlerden biri ise
			if(temp->ileri==NULL || temp->geri==NULL)
			{//tempin ilerisi veya gerisi bos ise
				cout<<sayi+1<<". yerde isaret hatasi var"; 
				return 1;
			}
			if(temp->ileri->icerik[0]=='*' || temp->ileri->icerik[0]=='/' || temp->ileri->icerik[0]=='+' || temp->ileri->icerik[0]=='-' || temp->ileri->icerik[0]=='^' || temp->ileri->icerik[0]=='%')
			{//tempin ilerisinin içeriðinin ilk karakteri yukarýdakilerden herhangi biri ise
				cout<<sayi+2<<". yerde isaret hatasi var"; 
				return 1;
			}
			if(temp->geri->icerik[0]=='*' || temp->geri->icerik[0]=='/' || temp->geri->icerik[0]=='+' || temp->geri->icerik[0]=='-' || temp->geri->icerik[0]=='^' || temp->geri->icerik[0]=='%')
			{ //tempin gerisinin içeriði yukaridakilerden herhangi biri ise
				cout<<sayi<<". yerde isaret hatasi var"; 
				return 1;
			}
		}
		
		temp=temp->ileri; //tempin ilerisini tempe atar
		sayi++; //sayiyi yani sayaci bir attýrýr
	}
	if(s.top()!=0)  
	{//stackin boþ olup olmadýðýný kontrol eder. boþ deðilse
		cout<<"parantez kapatilmamis";
		return 1;
	}
	
}

int oncelik(char krk)  //atadýðýmýmz tempin içeriðinin ilk karakteri
{
	if(krk=='a'||krk=='s'||krk=='c'||krk=='t'||krk=='l') return 5;//a,s,c,t,l ise 5 degeri döndürsün
    else if(krk=='^'||krk=='%') return 4;    //^ veya % ise 4 döndürsün
    else if(krk=='*'||krk=='/') return 3;     //* veya / ise 3 döndürsün
    else if(krk=='+'||krk=='-') return 2;    //+ veya - ise 2 döndürsün
	else if(krk=='('||krk=='['||krk=='{') return 1;  // (,[ veya { ise 1 döndürsün
	else return 0;   //hiçbiri deðilse 0 döndürsün
}

void sabit_yerlestir(Listeptr l)  //listemizi l olarak tanýmladýk
{
	Elemanptr temp;  //elemanptr türünde temp'i tanýmladýk
	temp=l->bas;   //listenin basýný temp'e atadýk
	while(temp!=NULL) //temp bos ise
	{
		if(temp->icerik[0]=='P'||temp->icerik[0]=='p') sprintf(temp->icerik, "%2.6f", PI);//  tempin içeriðindeki karakter katarýna yazar
		else if(temp->icerik[0]=='E'||temp->icerik[0]=='e') sprintf(temp->icerik, "%2.6f", E); //tempin içeriðindeki karakter katarýna yazar
		temp=temp->ileri;  //tempin ilerisini tempe aktarýr
	}
}

Listeptr postfix(Listeptr liste)  //liste türünde posfix tanýmlandý ve listemizi parametreye atadýk
{
	int oncelikA,oncelikU;   //iki deðiþkenimizi tanýmladýk
	Listeptr yeni=yeni_liste(); //liste ptr türünde yeni tanýmladýk yeni liste fonksiyonunu atadýk
	Elemanptr temp,temp1;       //elemanptr türünde temp ve temp1 tanýmladýk
	stack <Elemanptr> s;        //elemanptr türünde s adýnda stak oluþturduk
	temp=liste->bas;            //listenin basýný temp'e atadýk
	while(temp!=NULL)      //temp bos ise
	{
		temp1=temp->ileri;   //temp'in ilerisini tmp1 e atadýk
		if(temp->icerik[0]!='a' && temp->icerik[0]!='t' && temp->icerik[0]!='c' && temp->icerik[0]!='s' && temp->icerik[0]!='l' && temp->icerik[0]!='*' && temp->icerik[0]!='/' && temp->icerik[0]!='+' && temp->icerik[0]!='-' && temp->icerik[0]!='^' && temp->icerik[0]!='%' && temp->icerik[0]!='(' && temp->icerik[0]!='{' && temp->icerik[0]!='[' && temp->icerik[0]!=')' && temp->icerik[0]!='}' && temp->icerik[0]!=']')
		{ //tempin içeriðindeki ilk karakter a,t,c,s,l,*/+-! gibi karakterlerden farklý ise
			listeye_ekle(temp,yeni); //temp'i ve yeni listeyi liste_ekleye gönderir
		}
		else if(temp->icerik[0]=='(' || temp->icerik[0]=='[' || temp->icerik[0]=='{') //tempin içeriðinde basta ([{ varsa
		{
			s.push(temp); //bu tempi stack'e ekler
		}
		else if(temp->icerik[0]==')') //yukarýdaki deðilse eger ) ise
		{
			while(s.top()->icerik[0]!='(')  //stackteki tempin basýnýn icerigi ( farklý ise
			{
				listeye_ekle(s.top(),yeni);  //stackin basýndaki tempi ve yeni listeyi liste_ekleye göndderir
				s.pop();  //stackten tempi cýkaracak
				
			}
			s.pop(); //stackten cýkaracaktýr
		}
		else if(temp->icerik[0]==']')//yukarýdakiler deðilse eger ] ise
		{
			while(s.top()->icerik[0]!='[')//stackteki tempin basýnýn iceriði [ ise
			{
				listeye_ekle(s.top(),yeni); //stackin basýndaki tempi ve yeni listeyi liste_ekleye gönderir
				s.pop();				//stackten cýkarýr
			}
			s.pop();  //burda stackten cýkarýr
		}
		else if(temp->icerik[0]=='}') //yukarýdakiler deðilse eger } ise
		{
			while(s.top()->icerik[0]!='{') //stackin basýndaki tempin içerigi { farklý olana kadar
			{
				listeye_ekle(s.top(),yeni); //listenin basýndaki tempi ve yeniyi lisye_ekle ye gönder
				s.pop();   //stackten cýkar
				
			}
			s.pop();  //burda da stackten cýkar
		}
		else if(s.empty()) s.push(temp);    //yukarýdakiler degilse ve stack bos ise temp i stacke ekle
		else //yukarýdakiler deðilse
		{
			oncelikU=oncelik(temp->icerik[0]);   //tempin içeriðinin ilk karakterini ocelik fonk.gönderir ve oncelikU ya atar
			oncelikA=oncelik(s.top()->icerik[0]);//stackteki bastaki tempin iceriginin ilk karakterini oncelik fonk. gönderir ve oncelikA ya atar
			if(oncelikU>oncelikA)  //dönen degerlere göre karþýlastýrma saglanýlýrsa
			{
				s.push(temp); //stacke temp i atasýn
			}
			else  //saglanmaz ise 
			{
				while(oncelikU<=oncelikA) //sart saglandýðý müddetce
				{
					listeye_ekle(s.top(),yeni);   //stack'i ve yeni listeyi liste_ekleye gönderir
					s.pop();     //stackten cýkarýr
					if(s.empty()) oncelikA=0;  //stack bos ise oncelikA ya 0 degeri atanýr
					else oncelikA=oncelik(s.top()->icerik[0]);	//bos degilse stackin basýndaki tempin içeriginin 				
				}                                               //ilk karakteri oncelik den dönen deger atanýr oncelikA'ya
				s.push(temp);    //temp stack'e atanýr
			}
		}
		temp=temp1;     //temp1 temp degiskenine atanýr
	}
	while(!s.empty())  //stack bos olmadýgý müddetce
	{
		listeye_ekle(s.top(),yeni);  //stackin basýndaki temp ve yeni liste liste_ekle fonk. gönderilir
		s.pop();   //stackten cýkartýlýr
	}
	free(liste);   //liste icin ayrýlmýþ alan bosaltýlýr yada kaldýrýlýr (garbage collector)
	return yeni;   //yeni degerini döndürecektir.
}

void coz(Listeptr l)   //listeyi l adýnda listeptr türündeki l ye atadýk
{
	Elemanptr temp,sayi1,sayi2;  //elemanptr türünde temp,sayi1,sayi2 tanýtýldý
	temp=l->bas;      //listenin basýný tempe atadý
	double sonuc;     //sonuc degiskeni tanýtýldý
	while(l->bas!=l->son)  //listenin basý listenin sonundan farklý oldugu müddetce
	{
		if(oncelik(temp->icerik[0])<5&&oncelik(temp->icerik[0])>1) //oncelik fonk.dan gelen degerler karsýlastýrmasý saglanýrsa
		{
			sayi1=temp->geri;   //sayi1 e tempin gerisi atanýr
			sayi2=sayi1->geri;  //sayi2 ye sayi1 in gerisi atanýr
			switch(temp->icerik[0])  //tempin içeriðinin ilk karakteri;
			{
				case '+' : sonuc=atof(sayi2->icerik)+atof(sayi1->icerik); break;//icerikleri aritmetik iþlemlere alýp sonuca atar
				case '-' : sonuc=atof(sayi2->icerik)-atof(sayi1->icerik); break;
				case '*' : sonuc=atof(sayi2->icerik)*atof(sayi1->icerik); break;
				case '/' : sonuc=atof(sayi2->icerik)/atof(sayi1->icerik); break;
				case '^' : sonuc=pow(atof(sayi2->icerik),atof(sayi1->icerik)); break;  //üslü içerikler için float olarak dönüþtürüp sonuca atar
				case '%' : sonuc=fmod(atof(sayi2->icerik),atof(sayi1->icerik)); break;  //modunu alýr
			}
			sprintf(temp->icerik, "%2.6f", sonuc);   //karakter katarýný yazdýrýr
			if(sayi2->geri==NULL)   //sayi2 nin gerisi bos ise
			{
				temp->geri=NULL;   //tempin gerisi bos olsun
				l->bas=temp;       //listenin basýna tempi ata
			}
			else    //bos deðilse
			{
				temp->geri=sayi2->geri;   //sayi2nin gerisini tempin gerisine atasýn
				sayi2->geri->ileri=temp;   //sayi2 nin gerisinin ilerisine tempi atasýn
				free(sayi1);       //sayi1 ve sayi2 için tahsis edilen alanlar temizlenilir
				free(sayi2);                    //garbage collector
			}
		}
		else if(temp->icerik[0]=='!')   // degilse eger tempin içeriðinin ilk karakteri ! e esitse
		{
			sayi1=temp->geri;          //tempin gerisini sayi1 e atasýn
			sonuc=1;                   //sonuca 1 degerini atasýn
			if(atoi(sayi1->icerik)!=0)  //sayi1 ini iceriðindeki int deger 0 dan farklý ise
			{
				for(int i=atoi(sayi1->icerik);i>0;i--) //bu sarta göre for döngüsü oluþturup azalt
				{
					sonuc*=i;    //sonucu i ile carpýp sonuca ekleyelim
				}	
			}
			sprintf(temp->icerik, "%2.1f", sonuc);   //tempin iceriðindeki  sonucu katara ekler
			if(sayi1->geri==NULL)    //sayi1in gerisi bos ise
			{
				temp->geri=NULL;   //tempin gerisini bos yap
				l->bas=temp;       //tempi listenin basýna aktar
			}
			else        //bos degilse
			{
				temp->geri=sayi1->geri;     //tempin gerisine sayi1 in gerisini atasýn
				sayi1->geri->ileri=temp;    //sayi1in geisinin ilerisine tempi atasýn
				free(sayi1);         //sayi1 için ayrýlan alaný boþaltsin
			}
		}
		else if(oncelik(temp->icerik[0])==5)  //yukarýdakþ degilse ve oncelikten dönn deger 5 ise
		{
			sayi1=temp->geri;      //tempin gerisini sayi1 e atasýn
			switch(temp->icerik[0])   //tempin iceriðinin ilk karakteri;
			{
				case 'l' :    //l ise
				if(temp->icerik[1]=='n') sonuc=log(atof(sayi1->icerik));//ln ise sonuca ln islemini uygula
				else if(temp->icerik[2]=='g') sonuc=log10(atof(sayi1->icerik));//log ise log islemini uygula
				break;   //bitir
				case 's' :     //s ise
				if(temp->icerik[1]=='i') sonuc=sin(atof(sayi1->icerik)); //sin ise sonuca sin islemini ata
				else if(temp->icerik[1]=='g')  //degilse ve sg islemi varsa
				{
					if(atof(sayi1->icerik)>0) sonuc=1;   //islem sýfýrdan büyükse sonuc 1 olsun
					else if(atof(sayi1->icerik)<0) sonuc=-1;  //sýfýrdan küçük ise -1 olsun
					else sonuc=0;   //o da degilse sonuc 0 olsun
				}
				break; //bitir
				case 'c' :   //c ise
				if(temp->icerik[2]=='s') sonuc=cos(atof(sayi1->icerik));  //cos isemi yapýp sonuca atasýn
				else if(temp->icerik[2]=='t') sonuc=1/tan(atof(sayi1->icerik));   //cot islemi yapýp sonuca atasýn
				break; //bitir
				case 't' : sonuc=tan(atof(sayi1->icerik)); break;  // t ise tan islemini yapýp sonuca atasýn
				case 'a' :   //a ise
				if(temp->icerik[1]=='s') sonuc=asin(atof(sayi1->icerik));   //asin ise asin islemi yapýp sonuca atasýn
				else if(temp->icerik[1]=='t') sonuc=atan(atof(sayi1->icerik));//atan ise atan islemi yapýp sonuca atasýn
				else if(temp->icerik[1]=='c')    //sonraki c ise
				{
					if(temp->icerik[3]=='s') sonuc=acos(atof(sayi1->icerik));  //s ise acos islemi yapýp sonuca atasýn
					else if(temp->icerik[3]=='t') sonuc=1-atan(atof(sayi1->icerik));  //t ise acot islemi yapýp sonuca atasýn
				}
				break; //bitir
			}
			sprintf(temp->icerik, "%2.6f", sonuc);   //tempin içeriði sonucu katarý yazar
				if(sayi1->geri==NULL)        //sayi1 in gerisi bos ise
				{
					temp->geri=NULL;     //tempin gerisi bos olsun
					l->bas=temp;         //tempi listenin basýna atasýn
				}
				else   //bos deðilse
				{
					temp->geri=sayi1->geri;    //sayi1 in gerisini tempin gerisine atasýn
					sayi1->geri->ileri=temp;   //sayi1 in gerisinin ilerisini temp oluþtursun
					free(sayi1);     //sonra sayi1 için oluþturulan alaný boþaltsýn (garbage collector)
				}
		}
	temp=temp->ileri;     //tempin ilerisini tempe atasýn
	//listele(l);
	}
}

double islem(char denklem[])    //islem fonksiyonumuzu olusturduk
{	
	Listeptr liste=yeni_liste();  //liste adýnda tanýmlamamýzý yaptýk
	int i=krk_knt(denklem);       //denklemi krk_knt fonksiyonuna gönderip gelen degeri i degiskenine atadýk
	if(i!=-1)    //gelen deger -1'den farklý ise
	{
		cout<<i+1<<". karakater bilinmiyor."; //iyi 1 arttýr ve yazmayý gerceklestir
		exit(0);      //cýkýsa yönelt
	}
	bagli_yapma(denklem,liste);  //baglý_yapma fonksiyonuna denklemi ve listeyi gönderiyor.
	if(hata(liste)==1) exit(1);  //listeyi hata fonksiyonuna gönderir hatadan 1 dönerse cýkýsa git
	//listele(liste);
	sabit_yerlestir(liste);//listeyi  sabit yerlestir fonksiyonuna gönderiyoruz pi ve exp için
	liste=postfix(liste);  //listeyi postfix fonksiyonuna gönderdikten sonra listeye tekrar atar
	listele(liste);       //listeyi listele fonk. nuna gönderir
	coz(liste);           //listeyi coz fonksiyonuna gönderir
	listele(liste);	      //listeleme islemini tekrarlaasýn
	return atof(liste->bas->icerik);;   //listeninbasýndaki icerigi float degerini döndürsün
	
}

int main()
{
	double sonuc;  //sonuc icin degiþken tanýmladýk
	char denklem[50];  //girilecek denklem için deðisken tanýmlamasý yaptýk
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"++      Lutfen Trigonometrik ve Logaritmik ifadeleri () icinde kullaniniz.      ++"<<endl;
	cout<<"++++                Pi Sayisi icin (pi yada PI) kullaniniz.                   ++++"<<endl;
	cout<<"++++++                Exp(e) sayisi icin:exp kullaniniz.                    ++++++"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"++                                                                              ++"<<endl;
    cout<<"++                Ornek denklem: sin(pi/2)+ln(exp)+log(10)+(3%2)!               ++"<<endl; 
    cout<<"++                                                                              ++"<<endl;                                      
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"Denklemi Yaziniz:"<<endl;
	cin>>denklem;	//denklem girisini aldýk
	cout<<"Denklemin Postfixi ve Sonucu:";
	sonuc=islem(denklem); //denklemi islem fonksiyonuna gönderdik
	cout<<endl;
	cout<<"Denklemin Yuvarlatilmis Sonucu : "<<endl<<round(sonuc);
}
