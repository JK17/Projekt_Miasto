#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include <fstream>
#include<ctime>
#include<cstdlib>
using namespace std;
//====================================================================================
class Kibic;
class Miasto
{
  int rozmiar;
  vector<Kibic> kibice;
  friend class Kibic;
public:
  void zaludnij (int N);
  void ewoluuj(double r);
  void zapisz_i_narysuj ();
  int liczba_kibicow ();
};
//========================================================================================
class Kibic
{
  friend class Miasto;
  double x, y;
  int klub;
public:
double zadowolenie (Miasto m, double r);
void przeprowadzka(double r);
double odleglosc_kibicow();
Kibic ();
Kibic (double xk, double yk, int barwa);

};
//====================================================================================
Kibic::Kibic(double xk, double yk, int barwa)
{
  x=xk;
  y=yk;
  klub=barwa;

}
//======================================================================
void Miasto::zaludnij(int N)
{
  for(int i=0; i<N; i++)
  {

    double xk, yk; int barwa;
    xk=25*((double)rand()/RAND_MAX);
    yk=25*((double)rand()/RAND_MAX);
    if (i%2==0)
    {
      barwa=0;
    }
    if (i%2==1)
    {
      barwa=1;
    }
    kibice.push_back(Kibic (xk, yk, barwa));
  }
}

//=======================================================================================
double Kibic::zadowolenie (Miasto m, double r)
{
  double zadowolenie=-1;
  for(int i=0; i<m.kibice.size();i++)
  {
      double odleglosc;
      odleglosc = sqrt(pow((x-m.kibice.at(i).x),2)+pow((y-m.kibice.at(i).y),2));//------------------sprawdzam odleglosc miedzy kibicami
      if(odleglosc<=r)//------------------------------------------------------------------------jesli odleglosc jest odpowiednia, spradzam klub
      {
        if(klub==m.kibice.at(i).klub)//-----------------------------------------------------------------------------jesli ten sam klub dodaje zadowolenie
        {
          zadowolenie += 1;
        }
        else//----------------------------------------------------------------------------------------------------------------------jesli rozne kluby odejmuje zadowolenie
        {
          zadowolenie += -1;
        }
      }
    }
    return zadowolenie;
  }
  //=====================================================================================================================
  void Miasto::ewoluuj (double r)
  {
    double srednie_zadowolenie=0;
    for (int i=0; i<kibice.size();i++)
    {
      double aktualne_zadowolenie=kibice.at(i).zadowolenie(*this, r);
      srednie_zadowolenie+=aktualne_zadowolenie;
      if(aktualne_zadowolenie<0)
      {
        kibice.at(i).przeprowadzka(r);
      }
    }
    cout <<"Srednie zadowolenie jest równe "<< srednie_zadowolenie/kibice.size() << endl;
  }
  //=============================================================================
  void Kibic::przeprowadzka(double r)
  {
    x+=r*cos((rand()/(double)RAND_MAX)*2*M_PI);
    y+=r*sin((rand()/(double)RAND_MAX)*2*M_PI);
    if(x>25)
    {
        x=x-25;
    }
    if(y>25)
    {
        y=y-25;
    }
    if(x<0)
    {
        x=x+25;
    }
    if(y<0)
    {
        y=y+25;
    }
  }
//====================================================================================
void Miasto::zapisz_i_narysuj()
{

    ofstream pliklegia("legia.txt");

    ofstream plikpolonia("polonia.txt");

    for(int i=0;i<kibice.size();i++)
    {
        if(kibice.at(i).klub==0)
        {
          pliklegia<<kibice.at(i).x<< '\t'<<kibice.at(i).y<<endl;
        }
        if(kibice.at(i).klub==1)
        {
          plikpolonia<<kibice.at(i).x<< '\t' <<kibice.at(i).y<<endl;
        }
    }
    pliklegia.close();
    plikpolonia.close();

    ofstream skrypt("skrypt.gp");

    skrypt<<"plot \"legia.txt\" with points pointtype 7 lt 2,\"polonia.txt\" with points pointtype 7 lt 7" << endl;
    skrypt<<"pause -1 \"Wciśnij ENTER\" ";

    skrypt.close();
    system("gnuplot skrypt.gp" );
}
//=========================================================================================
int main()
{
  srand(time(0));
  int N;
  cout << "Podaj liczbe mieszkancow" << endl;
  cin >> N;
  //cout << "Czy cos nawalilo? " << cin.fail() << endl;
  cout << "Podaj liczbe lat zycia" << endl;
  int L;
  cin >> L;
  //cout << "Czy cos nawalilo? " << cin.fail() << endl;
  double r;

  do
  {cout << "Podaj interesujący Cię promień z przedzialu (0;25>" << endl;
  cin >> r;
  }
  while(r>25 || r<0);

  Miasto m;
  m.zaludnij(N);
  for(int i=0;i<L;i++)
  {
  m.ewoluuj(r);
  }
  m.zapisz_i_narysuj();

  return 0;
}
