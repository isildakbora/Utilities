#include <iostream>
#include <iomanip>
void ErrorBand(TString f, double percent_UP, double percent_DOWN, double x_MIN, double x_MAX){
const int n=1000;
TF1 *func= new TF1("FUNC",f,x_MIN, x_MAX);
TGraph *graph = new TGraph(n);
 
Double_t x[n], y[n];
Double_t y_UP, y_DOWN;
double increment=(x_MAX-x_MIN)/(0.5*(n-2));
    for (int i=0;i<n/2;i++)
    {
        x[i]   =x_MIN+i*increment;
        x[n-i-1] =x_MIN+i*increment;
        y_UP   =(1+percent_UP)*func->Eval(x[i]);
        y_DOWN =(1-percent_DOWN)*func->Eval(x[i]);
        y[i]=y_UP;
        y[n-i]=y_DOWN;
        cout.precision(5);
        cout<<fixed<<i<<"\t"<<n-i-1<<"\t"<<x[i]<<"\t"<<x[n-i-1]<<"\t"<<y_UP<<"\t"<<y_DOWN<<endl;
        graph->SetPoint(i,x[i],y_UP);
        graph->SetPoint(n-i-1,x[n-i-1],y_DOWN);
         
    }
 
 
graph->SetFillColor(kYellow-6);
graph->Draw("AF");
 
}
 
void ErrorBand(TF1 *f, double percent_UP, double percent_DOWN, double x_MIN, double x_MAX)
{
    const int n=1000;
    TF1 *func;
    func=f;
    cout<<"func=f"<<endl;
    TGraph *graph = new TGraph(n);
 
    Double_t x[n], y[n];
    Double_t y_UP, y_DOWN;
    double increment=(x_MAX-x_MIN)/(0.5*(n-2));
    for (int i=0;i<n/2;i++)
    {
        x[i]   =x_MIN+i*increment;
        x[n-i-1] =x_MIN+i*increment;
        y_UP   =(1+percent_UP)*func->Eval(x[i]);
        y_DOWN =(1-percent_DOWN)*func->Eval(x[i]);
        y[i]=y_UP;
        y[n-i]=y_DOWN;
        cout.precision(5);
        //cout<<fixed<<i<<"\t"<<n-i-1<<"\t"<<x[i]<<"\t"<<x[n-i-1]<<"\t"<<y_UP<<"\t"<<y_DOWN<<endl;
        graph->SetPoint(i,x[i],y_UP);
        graph->SetPoint(n-i-1,x[n-i-1],y_DOWN);  
    }
 
 
    graph->SetFillColor(kYellow-6);
    graph->Draw("AF");
 
}
 
TGraph* ErrorBand(TH1 *histo[6], double x_MIN, double x_MAX)
{
 
    int n =histo[0]->GetNbinsX();
    TGraph *graph = new TGraph(n);
 
    Double_t x[n], y[n];
 
 
    for (int i=0;i<n/2;i++)
    {
            x[i]   =histo[0]->GetBinCenter(i);
            x[n-i-1] =histo[0]->GetBinCenter(n-i-1);
             
            double tmp_min, tmp_max;
            for(j=0;j>6;j++)
            {
                tmp_min=  histo[j]->GetBinContent(i); 
                tmp_max=  histo[j]->GetBinContent(i);
                 
                if(tmp_min < histo[j]->GetBinContent(i)){ tmp_min = histo[j]->GetBinContent(i);}
                if(tmp_max > histo[j]->GetBinContent(i)){ tmp_min = histo[j]->GetBinContent(i);}
            }
            y[i]=tmp_max;
            y[n-i]=tmp_min;
            cout.precision(5);
            //cout<<fixed<<i<<"\t"<<n-i-1<<"\t"<<x[i]<<"\t"<<x[n-i-1]<<"\t"<<y_UP<<"\t"<<y_DOWN<<endl;
            graph->SetPoint(i,x[i],tmp_max);
            graph->SetPoint(n-i-1,x[n-i-1],tmp_min);
             
    }
 
    return graph;
}
 
TGraph* ErrorBand(TGraphErrors Graph)
{
 
    int n =Graph->GetN();
 
    TGraph *graph = new TGraph(2n);
 
    Double_t x[2n], y[2n];
 
 
    for (int i=0;i<n;i++)
    {
        Graph->GetPoint(i,x[i],y[i]);
        y[i]=y[i]+Graph->GetErrorY(i);
        x[n-i-1]=x[i];
        y[n-i-1]=y[i]-Graph->GetErrorY(i);
         
        graph->SetPoint(i,x[i],y[i]);
        graph->SetPoint(n-i-1,x[n-i-1],y[n-i-1]);
             
    }
 
    return graph;
}