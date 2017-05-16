#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct alumno{
    char nombre [200];
    char ape [200];
    char fn [11];
    char ci [12];
    float notas [30];
    char dir [500];
};

int main () {
    alumno alum;
    streampos size;
    int cursor=0,repetir=0;
    ofstream archivocrear("registro.csv",ios::trunc);  
    ifstream leerarchivo("datos.bin", ios::in|ios::binary|ios::ate);
    if(leerarchivo.is_open()){
        size = leerarchivo.tellg();
        leerarchivo.seekg (0, ios::beg);
           
        for(int x=0;x<size;x=x+1044){  
            leerarchivo.seekg(x);//el 1044 es por la suma de los bits de la estructura que tiene cada registro
                                 // 200 + 200 +11+12+(30*4)+500+1 , el 1 es para el nuevo registro                   
            //proceso para leer del archivo "datos.bin"
            leerarchivo.read (alum.nombre, 200);
            leerarchivo.read (alum.ape, 200);
            leerarchivo.read (alum.fn, 11);
            leerarchivo.read (alum.ci,12);
            for (int i = 0; i < 30; i++){
                leerarchivo.read((char *)(&alum.notas[i]),sizeof(alum.notas[i]));  //esta linea de codigo,permite leer un vector float de un archivo binario
            }
            leerarchivo.read (alum.dir,500);
            //fin del proceso
            
            
            //proceso para guardar en el nuevo archivo "registro.csv"
            
            archivocrear<<alum.nombre<<","<<alum.ape<<","<<alum.fn<<","<<alum.ci<<",\"";
            for(int x=0;x<30;x++){
                archivocrear<<alum.notas[x];
                if(x==29){
                    archivocrear<<"\",\"";
                }else{
                    archivocrear<<",";
                }
            }
            archivocrear<<alum.dir<<"\"\n";//fin del proceso
        }
        cout << "el archivo termino su proceso de transferencia\n\n";
        leerarchivo.close();
    }else {
        cout<<"por algun motivo, el programa no encontro el archivo\n";
        cout<<"por favor,asegurese de que el archivo binario se encuentre en la carpeta\n";
    }
    system("pause");
    return 0;
}
