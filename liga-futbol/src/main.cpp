    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <iomanip>
    //Colores para la letra en terminal
    #define ROJO "\033[31m"
    #define AZUL "\033[34m"
    #define MORADO "\033[35m"
    #define CYAN "\033[36m"
    #define RESET "\033[0m"
   
    //Estructuras y configuraciones
    struct partido {
        std::string fecha;
        std::string local;
        std::string visitante; 
        int gl;
        int gv;
    }; 
    struct equipo{
        std::string league; 
        int win, draw, lost; 
        int PJ=0; int PG=0; int PE=0; int PP=0; 
        int GF=0; int GC=0; int DG=0; int P=0;
    };
   
    //Funciones
    void readconf(std::vector <equipo> &teams){
        std::ifstream file("data/config.txt"); 
            if(!file){
            std::cout<<ROJO <<"No es posible abrir el archivo :c\n" << RESET;  //caso de error
            return ;
            }
            std::string line;
            while (getline (file, line)) {
            if (line.empty()) continue;
            if (line.find("=") != std::string::npos) continue; //remueve elementos de "puntitos" para no mostrar en la tabla 
            if (line.find(":") != std::string::npos) continue; //remueve "puntitos" para no mostrar en la tabla 
            if (line.find("Liga") != std::string::npos) continue; //remueve el nombre de la liga para no hacerlo parte de la tabla 

            equipo e;
            e.league= line;
            teams.push_back(e);
        } }

    //Suma de puntos y partidos
    //se da una modificación en la estructura "match" 
    void act (equipo &e, int F, int C){    //F= A favor - C= En contra
        e.PJ++;
        e.GF += F;
        e.GC += C;
        e.DG += (F-C);

        if (F>C) {
            e.PG++;
            e.P += 3;
        } else if (F==C){
            e.PE++;
            e.P += 1;
        } else {
            e.PP++;
        }
    }
       // Permiso de uso de minúsculas
        std::string lower(std::string s){
        for (char &c : s) c = std::tolower(c);
        return s;}

    //construcción de los vectores principales
    std::vector<equipo> build (const std::vector<partido> match, std::vector<equipo> teams){
        for( int i=0; i<match.size(); i++){
        int local= -1;  //-1 gracias a que aún desconocemos la posición
        int visitante= -1;

        std::string ml = lower(match[i].local);
        std::string mv = lower(match[i].visitante);

    //Recibe los equipos cargados desde config.txt y los partidos y devuelve el vector con estadísticas actualizadas.
        for(int j = 0; j < teams.size(); j++){
            std::string nombre = lower(teams[j].league);
            if (nombre == ml) local = j;
            if (nombre == mv) visitante = j;
             }
        if(local != -1 && visitante != -1){
            act(teams[local], match[i].gl, match[i].gv);
            act(teams[visitante], match[i].gv, match[i].gl);
        }}
    return teams; 
    }
        //carga de partidos en partidos.txt
    int read(std::vector<partido> &partidos){
        std::ifstream arch("data/partidos.txt");
        if(!arch){
           std::cout<<ROJO;
        std::cout<<"No hay partidos guardados unu\n"<<RESET;
            return 0;
        }
        std::string line2;
        while(getline(arch, line2)){
            if (line2.empty()) continue;  //sigue a pesar de encontrar una línea vacía
            std::stringstream ss(line2);
            std::string fecha, l, v, gla, gva;

            getline(ss, fecha, '|'); //introduce la fecha
            getline(ss, l, '|'); //introduce el equipo local
            getline(ss, v, '|'); //introduce el equipo visitante
            getline(ss, gla, '|'); //goles del local
            getline(ss, gva, '|'); //goles del visitante

        //std::cout << "DEBUG -> gla: [" << gla << "] gva: [" << gva << "]\n";
            //El comando anterior permite revisar que lee "stoi" y donde puede haber un fallo del código
            partido p;
            p.fecha= fecha;  
            p.local = l;
            p.visitante = v;
            p.gl= std::stoi(gla);   //el "std" ayuda a evitar errores que detienen la actividad del programa
            p.gv= std::stoi(gva);
            partidos.push_back(p);
        }
        arch.close();
        return 0;
    }; 

    //registro y actualización de partidos
    void reg(std::vector <equipo> &teams, std::vector<partido>&match){    
        std::cout<<MORADO; 
        std::string x, y;  //equipos
        std::cout<<"Defina equipo local: ";
        std::cin.ignore();  //limpieza para tomar el dato bien
        std::getline(std::cin, x);
        std::cout<<"Defina equipo visitante: ";
        std::getline(std::cin, y);
        std::string xl=lower(x);
        std::string yl =lower(y); 

        std::cout<<"Ingresa la fecha de juego D/M/A :D "; //se agrega la fecha del partido
        int a,b,c;
        std::cin>>a>>b>>c; 

        int v, l;  //goles 
        std::cout<<"Goles equipo local: ";
        std::cin>>l;
        std::cout<<"Goles equipo visitante: ";
        std::cin>>v;
        
        bool ev=false , el=false;  //Aún no se conoce si el equipo existe 
        for (int i = 0; i < teams.size(); i++) {
        if (lower(teams[i].league) == xl) {el= true; }  //al demostrar que existe su valor se vuelve verdadero
        if (lower(teams[i].league) == yl) {ev= true; }}

        if (!el) {
        std::cout<<ROJO;
         std::cout << "El equipo local no existe\n"; std::cout<<RESET;
        return;}
        if (!ev) {
        std::cout<<ROJO;
        std::cout << "El equipo visitante no existe\n"; std::cout<<RESET; 
        return;} 
        if (x == y) {
        std::cout<<ROJO;
        std::cout << "No pueden ser el mismo equipo\n"; std::cout<<RESET; 
        return; }
            //opción de evitar partidos duplicados
        bool dup= false;

        for(int i=0; i<match.size(); i++) {
        std::string ml = lower(match[i].local);
        std::string mv = lower(match[i].visitante);
    if (
        (ml == x && mv == y) ||   // si se tiene un mismo equipo de local y otro de visitante
        (ml == y && mv == x)      // e invertido
    ) {
        if (match[i].fecha == std::to_string(a) + "|" + std::to_string(b) + "|" + std::to_string(c)){ //en la misma fecha...
        dup=true;
        break;} }
    }
          //el duplicado se asume como existente
        if (dup) {
        std::cout << ROJO << "Este partido ya fue registrado en esa fecha\n" << RESET;
        return;}
        
         //inicialización para el historial de partidos (partidos.txt)
        std::ofstream file("data/partidos.txt",std::ios::app); //salida del archivo
        if(file){
            file<<a<<"/"<<b<<"/"<<c<<"|"<<x<<"|"<<y<<"|"<<l<<"|"<<v<<"\n"; 
        }
        file.close();
        //Conteo dinámico de las jornadas
        int cont = 0;
        std::ifstream leer("data/fechas.txt");
        std::string line;
        while (getline(leer, line)) {
        if (line.find("Jornada") != std::string::npos)
        cont++; }
        leer.close();

         //Inicialización del historial de jornadas (fechas.txt)
        std::ofstream fechas("fechas.txt",std::ios::app);    
        if (fechas){  
            fechas<<"Jornada "<<cont + 1<<std::endl;
            fechas<<a<<"|"<<b<<"|"<<c<<" | "<<x<<" "<<"VS"<<" "<<y<<std::endl;
            fechas<<"Fin de la jornada\n";
        } fechas.close();
        //Agregar al vector partidos
        partido p;
        p.fecha= std::to_string(a) + "|" + std::to_string(b) + "|" + std::to_string(c);
        p.local= x;
        p.visitante = y;
        p.gl= l;
        p.gv= v;
        std::cout<<std::endl;


        match.push_back(p);

        // Actualización de  estadísticas en memoria 
        for (int i = 0; i < (int)teams.size(); i++) {
        if (lower(teams[i].league) == lower(x)) act(teams[i], l, v);
        if (lower(teams[i].league) == lower(y)) act(teams[i], v, l);
        }
        if(l>v){
            std::cout<<"Ganador del partido: "<<x<<std::endl;
        }
        else if(l<v){
            std::cout<<"Ganador del partido: "<<y<<std::endl;
        } else {
            std::cout<<"Em-Pata-dos\n";
        }; 

        std::cout<<RESET; 
    return;
        };

    void org(std::vector <equipo> &teams){
         //Se ordena el vector por puntos
        std::sort(teams.begin(), teams.end(), [] (equipo x, equipo y){
            //Opción de desempate
            if (x.P !=y.P) 
             return x.P > y.P; //Primero se evalua por empate de puntos 

            if(x.DG!=y.DG)
            return x.DG>y.DG; //Si estan los puntos empatados, ahora es diferencia de goles

            return x.GF > y.GF;//Finalmente, se evaluan los goles a favor y gana el de mayoría
        return x.P > y.P;});
    }

    //Visualización de la tabla 
    void tabla (std::vector<equipo> teams){
    //std::vector<equipo> construirTabla(std::vector<partido> partidos, ConfigLiga config);{}
        org(teams);
        std::cout<<CYAN; 
        std::cout<<"Liga Huevito ^w^";
        //Representación de las columnas
        std::cout<<"Tabla de posiciones\n";
        std::cout<<std::left<< 
        std::setw(5)<<"Pos"<<std::setw(16)<<"Equipo"<<
        std::setw(5) << "PJ"<< std::setw(5)<<"PG"<<
        std::setw(5)<<"PE" << std::setw(5)<< "PP"<<
        std::setw(5)<<"GF"<<std::setw(5)<< "GC"<<
        std::setw(5)<<"DG"<<std::setw(5)<< "PTS"<<std::endl;

        std::ofstream arch("data/tabla.txt");

        //Representación de las filas 
        for(int i=0; i<teams.size(); i++){
            std::cout<<AZUL;
            std::cout<<std::left<<
                    std::setw (5)<<i+1<< 
                    std::setw (16)<<teams[i].league<<
                    std::setw (5) <<teams[i].PJ<<
                    std::setw (5)<<teams[i].PG<<
                    std::setw (5)<<teams[i].PE<<
                    std::setw (5)<<teams[i].PP<<
                    std::setw (5)<<teams[i].GF<<
                    std::setw (5)<<teams[i].GC<<
                    std::setw (5)<<teams[i].DG<<
                    std::setw (5)<<teams[i].P <<std::endl;
            arch<<i+1<< " " <<teams[i].league<<" "<<
            teams[i].PJ<<" " <<teams[i].PG<<" "<<
            teams[i].PE<<" " <<teams[i].PP<<" "<<
            teams[i].GF<<" "<<teams[i].GC<<" "<<
            teams[i].DG<<" "<<teams[i].P<<"\n"; std::cout<<RESET;
                }}       
    

    //visualización del historial de partidos
    int history(){
        std::ifstream file("partidos.txt");
        std::string line3;
        if (!file) {
        std::cout << ROJO << "No hay historial de partidos\n" << RESET;
        return 0;
    }
        while (getline(file,line3)){
            std::cout<<line3<<std::endl;
        }
        return 0;
    }
    //Visualización del historial de jornadas
     int date(){
        std::ifstream file("fechas.txt");
        std::string line4;
             if (!file) {
        std::cout << ROJO << "No hay historial de jornadas\n" << RESET;
        return 0;
    }
        while (getline(file,line4)){
            std::cout<<line4<<std::endl;
        }
        return 0;
    }
    //edición de un partido antes creado 
    void edit(std::vector<partido>& match, std::vector<equipo>& teams) {
    std::string x, y;
    int a,b,c;
    std::cin.ignore();

    std::cout<<"Equipo local: ";
    std::getline(std::cin, x);
    std::cout<<"Equipo visitante: ";
    std::getline(std::cin, y);

    std::cout<<"Fecha (D / M / A): ";
    std::cin>>a>>b>>c;

    x = lower(x);
    y = lower(y);

    bool found = false; //se asume que aún no se ha encontrado el partido 

    for(int i=0; i<match.size(); i++){
        std::string ml = lower(match[i].local);
        std::string mv = lower(match[i].visitante);

        if(
            ((ml == x && mv == y) || (ml == y && mv == x)) &&
            match[i].fecha == std::to_string(a) + "/" + std::to_string(b) + "/" + std::to_string(c)
        ){
            found = true;
            std::cout<<"Partido encontrado:\n";
            std::cout<<match[i].local<<" VS "<<match[i].visitante
                     <<" ("<<match[i].gl<<"-"<<match[i].gv<<")\n";

            int nl, nv;
            std::cout<<"Nuevo marcador local: ";
            std::cin>>nl;
            std::cout<<"Nuevo marcador visitante: ";
            std::cin>>nv;

            match[i].gl = nl;
            match[i].gv = nv;
            break;
        }}
    if(!found){
        std::cout<<ROJO<<"No se encontró el partido\n"<<RESET;
        return;
    }
    //se edita en el archivo de texto
    std::ofstream file("partidos.txt");

    for(int i=0; i<match.size(); i++){
        file<<match[i].fecha<<"|"
            <<match[i].local<<"|"
            <<match[i].visitante<<"|"
            <<match[i].gl<<"|"
            <<match[i].gv<<"\n";
    }

    file.close();
    for(auto &e : teams){
        e.PJ = e.PG = e.PE = e.PP = 0;
        e.GF = e.GC = e.DG = e.P = 0;
    }
    teams = build(match, teams);
    std::cout<<CYAN<<"Resultado actualizado ^w^ \n"<<RESET;
}
    //determinar el ganador final de toda la liga
    void win(std::vector<partido>&match, std::vector<equipo>&teams){
       //reconstrucción de tabla
        for(auto&e : teams){
            e.PJ = e.PG = e.PE = e.PP = 0;
            e.GF = e.GC = e.DG = e.P = 0;
        }
        teams = build (match, teams);
        org(teams);
        std::cout << CYAN << "\n Los cua-nadores de la liga son ^w^ : "
              << teams[0].league<< "\n";
            std::cout << "Puntaje: "<< teams[0].P << "\n";
            std::cout << "DG: " << teams[0].DG << "\n"; 
            std::cout << "GF: " << teams[0].GF << "\n" << RESET;
    }
    //menu
    int menu (std::vector<equipo> &teams, std::vector<partido>&match){
    int opt;
     std::cout<<AZUL;
     std::ifstream config("config.txt");
     std:: string leaguename;

     if (config) {
    std::getline(config, leaguename);
    std::cout << leaguename << std::endl;
} else {
    std::cout << "No se pudo abrir config.txt unu\n"; //En caso de error al buscar el archivo de texto
}
config.close();

    std::cout<<ROJO<<"Bienvenido al pati-menu ^w^ \n"<<RESET;
    do{
        std::cout<<"1. Ver equipos\n";
        std::cout<< "2. Registrar resultado de un partido  \n" ;   
        std::cout<< "3. Ver tabla de posiciones  \n" ;   
        std::cout<< "4. Ver historial de partidos\n";
        std::cout<< "5. Ver historial de jornadas\n";
        std::cout<< "6. Editar un partido\n";
        std::cout<< "7. Finalizar liga\n";
        std::cout<< "8. Salir\n";
        std::cout<< "Seleccione una opcion: ";
        std::cin >> opt;
        std::cout<<RESET; 

    switch (opt){
    case 1:
    for (int i=0; i<teams.size(); i++){
            std::cout<<"-"<< teams[i].league<< "\n"<<std::endl;}
        break;
    case 2: 
    reg(teams,match);
    //reconstrucción de la tabla conforme se ingresen datos
     for (auto &e : teams) {
        e.PJ = e.PG = e.PE = e.PP = 0;
        e.GF = e.GC = e.DG = e.P = 0;
    }
    teams= build(match,teams);
    break;

    case 3:
    tabla (teams);
    break;
        
    case 4:
    history ();
    break;

    case 5:
    date ();
    break;

    case 6:
    edit(match,teams); 
    break;

    case 7:{
    win(match, teams);
    break;}

    case 8:{
    std::cout<<"Hasta luego player ^w^ ";
    break;}

    default:
    std::cout<<ROJO; 
    std::cout<<"Opción inválida X.X \n"; RESET;  
        break;

    }; } while (opt !=8);
return 0; }

    //ejecución
    int main (){
        std::cout<<AZUL;
        std::vector <equipo> teams;
        std::vector <partido> match; 
        readconf(teams);
        read(match);
        //std::cout << "Cantidad de partidos cargados: " << match.size() << std::endl;
        //el código anterior permite visualizar cuanto se ha guaradado para saber si hay algún error al guardar
        teams = build(match, teams);
        menu(teams,match);
        RESET;
        return 0;
    }
