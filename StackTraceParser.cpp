#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <set>
using namespace std;


class StackTrace
{
private:
    
    string stackTrace;
    string version;
    int frequency;
    
public:
    
    void setStackTrace(string newStackTrace)
    {
        stackTrace=newStackTrace;
    }
    
    string getStackTrace() const
    {
        return stackTrace;
    }
    
    void setVersion(string newVersion)
    {
        version=newVersion;
    }
    
    string getVersion() const
    {
        return version;
    }
    
    void setFrequency(int newFrequency)
    {
        frequency=newFrequency;
    }
    
    int getFrequency() const
    {
        return frequency;
    }
    
};

bool comparatorFunction(const StackTrace& a,const StackTrace& b)
{
    if ((a.getVersion() + a.getStackTrace()) < (b.getVersion() + b.getStackTrace()))
        return true;
    
    return false;
}

set<StackTrace,bool(*)(const StackTrace&,const StackTrace&)> _stackTraceSet(comparatorFunction);
set<StackTrace>::iterator _stackTraceIterator;

int main(int argc, const char * argv[])
{
    ifstream inputFile;
    inputFile.open("input.csv");
    
    string str,stktrc;
    
    if(inputFile.is_open())
    {
        while(getline(inputFile,str))
        {
            int j=-1,k=-1;
            
            k=(int)str.find("Message:");
            j=(int)str.find("Memory in use:");
            
            if(k!=-1 && j!=-1)
            {
                StackTrace tempStackTrace;
                tempStackTrace.setStackTrace(str.substr(k,j-k));
                
                k=-1;
                k=(int)str.find("Version:");
                
                if(k!=-1)
                {
                    tempStackTrace.setVersion(str.substr(k+8,7));
                }
                else
                {
                    tempStackTrace.setVersion("UNKNOWN VERSION");
                }

                cout<<tempStackTrace.getVersion()<<"\n";
                cout<<tempStackTrace.getStackTrace()<<"\n\n\n";

                _stackTraceIterator=_stackTraceSet.end();
                _stackTraceIterator = _stackTraceSet.find(tempStackTrace);
                
                if(_stackTraceIterator != _stackTraceSet.end())
                {
                    tempStackTrace.setFrequency(_stackTraceIterator->getFrequency()+1);
                    _stackTraceSet.erase(_stackTraceIterator);
                    _stackTraceSet.insert(tempStackTrace);
                }
                else
                {
                    tempStackTrace.setFrequency(1);
                    _stackTraceSet.insert(tempStackTrace);
                }
                
            }
            
            cout<<"___________________________________\n\n\n\n";
        }
        
        inputFile.close();
        
        ofstream outputFile("output.csv");
        
        for(_stackTraceIterator=_stackTraceSet.begin();_stackTraceIterator!=_stackTraceSet.end();_stackTraceIterator++)
        {
            outputFile<<"\""<<_stackTraceIterator->getStackTrace()<<"\", "<<_stackTraceIterator->getVersion()<<" , "<<_stackTraceIterator->getFrequency()<<"\n";
        }
    }
    else
        cout<<"ErrorFile Not Found!! File Not read!!\n\n";
    
    return 0;
}
