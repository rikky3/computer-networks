#include <iostream>
#include <math.h>

using namespace std;

class user{
	int ip[4], flag[5] = {}, nos, mBits, mBits1;
	
	int binaryToDecimal(int mBitsX){
		int sum = 0, result = 0, base = 1;
		
		for(int i = 7; i >= 8 - mBitsX; i--){
			sum += pow(10, i);
		}
		
		int temp = sum;
		while(temp){ 
			int lastDigit = temp % 10; 
			temp = temp / 10; 
			result += lastDigit * base; 
			base = base * 2; 
		}
		return result;   
	}
	
	int maskingBits(int s){
		if(s == 0)
			return 0;
		else{
			double mbits = ceil(log2(s));
			return mbits;
		}
	}
	
	public:
		void accept(){
			cout<<"Please enter your IP address:"<<endl;
			for(int i = 0; i < 4; i++)
				cin>>ip[i];
			
			if(ip[0] < 1 || ip[0] > 254)
			{
				cout<<"Invalid input:"<<endl;
				accept();
			}
		
			for(int i = 1; i < 4; i++)
				if(ip[i] < 0 || ip[i] > 254){
					cout<<"Invalid input:"<<endl;
					accept();
				}			
		}
		
		void subnet(){
			if(ip[0] < 127){
				cout<<"Class A, default mask 255.0.0.0"<<endl;
				flag[0] = 1;
			}
			else if(ip[0] <= 191){
				cout<<"Class B, default mask 255.255.0.0"<<endl;
				flag[1] = 1;
			}
			else if(ip[0] <= 223){
				cout<<"Class C, default mask 255.255.255.0"<<endl;
				flag[2] = 1;
			}
			else if(ip[0] <= 239){
				cout<<"Class D"<<endl;
				flag[3] = 1;
			}
			else{
				cout<<"Class E"<<endl;
				flag[4] = 1;
			}		
		}	
		
		void maskingB(){
			if(flag[0] == 1 || flag[1] == 1 || flag[2] == 1){	 //accept number of subnets
				cout<<"How many subnets?"<<endl;
				cin>>nos;
			}
			
			if(flag[0] == 1 && nos > 4194302){
				cout<<"You have exceeded the class A subnet limit, please re-enter"<<endl;
				maskingB();
			}
			else if(flag[1] == 1 && nos > 16382){
				cout<<"You have exceeded the class B subnet limit, please re-enter"<<endl;
				maskingB();
			}
			else if(flag[2] == 1 && nos > 62){
				cout<<"You have exceeded the class C subnet limit, please re-enter"<<endl;
				maskingB();
			}
			else if(flag[3] == 1 || flag[4] == 1)
				cout<<"Subnetting is not permitted for class D and E IP addresses."<<endl;
			else{
				mBits = maskingBits(nos);
				cout<<mBits<<" bits will be borrowed from the host part by the network part"<<endl;
			}
		}
		
		void subnetMask(){
			if(flag[0] == 1){
				if(mBits == 16){		
					cout<<"The new subnet mask is 255.255.255.0"<<endl<<"and the usable IP range is "<<ip[0]<<".255.255.1 to "<<ip[0]<<".255.255.254"<<endl;
				}
				else if(mBits > 16){		
					mBits1 = mBits - 16;
					cout<<"The new subnet mask is 255.255.255."<<binaryToDecimal(mBits1)<<endl<<"and the usable IP range is "<<ip[0]<<".255.255."<<(binaryToDecimal(mBits1) + 1)<<" to "<<ip[0]<<".255.255.254"<<endl;
				}
				else if(mBits > 8){
					mBits1 = mBits - 8;
					cout<<"The new subnet mask is 255.255."<<binaryToDecimal(mBits1)<<".0"<<endl<<"and the usable IP range is "<<ip[0]<<".255."<<binaryToDecimal(mBits1)<<".1 to "<<ip[0]<<".255.255.254"<<endl;
				}
				else
					cout<<"The new subnet mask is 255."<<binaryToDecimal(mBits)<<".0.0"<<endl<<"and the usable IP range is "<<ip[0]<<"."<<binaryToDecimal(mBits)<<".0.1 to "<<ip[0]<<".255.255.254"<<endl;
			}
			else if(flag[1] == 1){
				if(mBits > 8){		
					mBits1 = mBits - 8;
					cout<<"The new subnet mask is 255.255.255."<<binaryToDecimal(mBits1)<<endl<<"and the usable IP range is "<<ip[0]<<"."<<ip[1]<<"."<<ip[2]<<"."<<(binaryToDecimal(mBits1) + 1)<<" to "<<ip[0]<<"."<<ip[1]<<"."<<ip[2]<<".254"<<endl;
				}	//check?
				else
					cout<<"The new subnet mask is 255.255."<<binaryToDecimal(mBits)<<".0"<<endl<<"and the usable IP range is "<<ip[0]<<"."<<ip[1]<<"."<<binaryToDecimal(mBits)<<".1 to "<<ip[0]<<"."<<ip[1]<<".255.254"<<endl;
			}
			else if(flag[2] == 1)
				cout<<"The new subnet mask is 255.255.255."<<binaryToDecimal(mBits)<<endl<<"and the usable IP range is "<<ip[0]<<"."<<ip[1]<<"."<<ip[2]<<"."<<(binaryToDecimal(mBits) + 1)<<" to "<<ip[0]<<"."<<ip[1]<<"."<<ip[2]<<".254"<<endl;
		}
};

int main(){
	string ch;
	
	do{
    	user u;
    	u.accept();	
    	u.subnet();
    	u.maskingB();
    	u.subnetMask();
    
    	cout<<endl<<"Want to try with another IP? Enter Y"<<endl;
    	cin>>ch;
    }while(ch == "Y");
	
	return 0;
}