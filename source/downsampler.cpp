#include <vector>
#include <iostream> 
using namespace std;

template <typename T>
class Downsampler
{
    int m_nRate;
    public:

    Downsampler(int rate) : m_nRate(rate){}
    vector<T> downsample(vector<vector<T>> buffer)
    {
        vector<T> vecReturn;
        int nNextSegStartingIndex = 0;
        int nCounter = 0;
        
        for (const auto& vec : buffer)
        {
            int nBufferSize = vec.size();
            int nDownSampleElements = 0;

            for (int j = 0; j < (nBufferSize - nNextSegStartingIndex); j++)
            {
                if(!(j % m_nRate))
                    nDownSampleElements++;
            }

            for(int nIndex = 0; nIndex < nDownSampleElements; ++nIndex)
                vecReturn.emplace_back(vec[nIndex*m_nRate + nNextSegStartingIndex]); 

            nNextSegStartingIndex = (m_nRate - (nBufferSize - nDownSampleElements*m_nRate - nNextSegStartingIndex)) % m_nRate;
        }
        return vecReturn;
    }
};

int main ()
{
    Downsampler<int> ds(4);

    vector<vector<int>> buffer{{}, {}, {}, {0,1,2,3,4}, {5,6}, {7}, {8,9,10,11,12}, {13,14}, {15,16,17,18},
                               {19,20}, {21,22,23,24,25}, {26,27,28,29,30}, {31,32,33}};
    vector<int> result = ds.downsample(buffer);

    cout << "Original vector: ";
    for (const auto& vec : buffer)
    {
        for (const auto& r : vec)
        {
            cout << r << " ";
        }
    }
    cout << endl;
    cout << " --- --- --- --- " << endl;
    cout << "Downsampler vector: ";
    for (const auto& r : result)
    {
        cout << r << " ";
    }
    cout << endl;
}
