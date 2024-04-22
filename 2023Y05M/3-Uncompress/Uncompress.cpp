#include <bits/stdc++.h>
using namespace std;

#define LITREAL 0
#define RECALL1 1
#define RECALL2 2 

int getBootArea(string& bootArea);
int getDataType(string type);
string convertEndianL2B(string lEndian);
string getByte(int num);  

int main(void)
{
	int s = 0, index = 0, dataLength = 0, dataType = 0;
	string input, bootArea, output, byte; 
	
	cin >> s;
	
	byte = getByte(1);
	index++;
	while(byte[0] != '0'){
		bootArea += byte;
	//	cout << "byte:" << byte << endl;
		byte = getByte(1);
		index++;
	}
	//cout << "byte:" << byte << endl;
	bootArea += byte;
	//cout << "AAAAA" << endl;
	//cout << bootArea << endl;	
	
	dataLength = getBootArea(bootArea);
//	cout << dataLength << endl;
	while(index < s){
		string type = getByte(1);
		index++;
		dataType = getDataType(type);
		//cout << "dataType:" << dataType << endl;
		if(dataType == LITREAL){
			string bytesNum = type;
			int bytesNumDec = stoi(bytesNum, 0, 16);		
			int litrealLength = bytesNumDec >> 2;
	
			//cout << litrealLength << " AAAAAA " << endl;
			if(litrealLength <= 59){
				output += getByte(litrealLength + 1);
				//cout << "output: " << output << endl;
				index += (litrealLength + 1);
				//cout << output << endl;
			} 
			else {
				string lLittleEndian = getByte(litrealLength - 59);
				index += (litrealLength - 59);
			//	cout << "lLittleDndian " << lLittleEndian << endl;
				int l = stoi(convertEndianL2B(lLittleEndian), 0, 16) + 1;
			//	cout << "little endian " << lLittleEndian << "l " << l << endl;
				
				output += getByte(l);
			//	cout << "output: " << output << endl;
				index += l;
			}
		}
		else if(dataType == RECALL1){
			string lInfo = type;
		//	cout << olInfo << endl;
			
			int lInfoDec = stoi(lInfo, 0, 16);
			//cout << olInfoDec << endl;
			int l = ((lInfoDec &  0b00011100) >> 2) + 4;
			
			int o_h3 = (lInfoDec & 0b11100000) << 3;
			int lowerO = stoi(getByte(1), 0, 16);
			index++;
		//	cout << index << endl;
			int o = o_h3 | (lowerO & 255);
			
		//	cout << l << " l " << endl;
		//	cout << o << " o " << endl;
			if(o >= l)
				output += output.substr(output.length() - o * 2, l * 2);
			else {
				string temp = output.substr(output.length() - o * 2, o * 2);
				for(int i = 0; i < l; i += o){
					if(i + o <= l)
						output += temp;
					else
						output += temp.substr(0, (l % o) * 2);
				}
			}
		}
		else if(dataType == RECALL2){
			string lInfo = type;
			int lInfoDec = stoi(lInfo, 0, 16);
		//	cout << lInfo << endl;
			int l = (lInfoDec >> 2) + 1;
			
			string oInfoLEndian = getByte(2);
			index += 2;
			int o = stoi(convertEndianL2B(oInfoLEndian), 0, 16);
			
		//	cout << l << " l " << endl;
		//	cout << o << " o " << endl;
		
			if(o >= l)
				output += output.substr(output.length() - o * 2, l * 2);
			else {
				string temp = output.substr(output.length() - o * 2, o * 2);
				for(int i = 0; i < l; i += o){
					if(i + o <= l)
						output += temp;
					else
						output += temp.substr(0, (l % o) * 2);
				}
			}		
			
		//	cout << output << endl;
		}
	}
	
	for(int i = 0; i < output.length(); i += 16){
		string temp = output.substr(i, 16);
		cout << temp << endl;
	}
	 
	return 0;
}

int getBootArea(string& bootArea)
{
	int dataLength = 0;
	int ck[bootArea.length() / 2];

	for(int i = 0; i < bootArea.length() ; i+=2){
		string temp = bootArea.substr(i, 2);
		if(i + 2 < bootArea.length())
			ck[i / 2] = stoi(temp, 0, 16) - 128;
		else
			ck[i / 2] = stoi(temp, 0, 16); 
	}
	
	
	for(int i = 0; i < bootArea.length() / 2; i++)
		dataLength += ck[i] * pow(128, i);
		
	return dataLength;
}


int getDataType(string type)
{
	string byte = type.substr(1, 1);
//	cout << "type:" << type << " byte:" << byte << endl;
	int dataType = 0, low2bit = stoi(byte, 0, 16) & 3;
//	cout << low2bit << endl;
	if(low2bit == 0)
		dataType = LITREAL;
	else if(low2bit == 1)
		dataType = RECALL1;
	else if(low2bit == 2)
		dataType = RECALL2;
	return dataType;
}

string convertEndianL2B(string lEndian)
{
	string bEndian;
	int length = lEndian.length();
	
	for(int i = 0; i < length; i += 2){
		bEndian += lEndian[length - i - 2];
		bEndian += lEndian[length - i - 1];
	}
	//cout << "big endian" << bEndian << endl;
	return bEndian;
}

string getByte(int num)
{
	char bytes[2 * num];
	string result;
	
	for(int i = 0; i < 2 * num; i++)
		cin >> bytes[i];
	
	result = string(bytes, 2 * num);
	
	//cout << "result:" << result << endl;
	return result;
}
