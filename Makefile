all: main.o database.o hospital.o paciente.o simulador.o sensor.o sensorSO.o sensorFC.o sensorFR.o sensorTC.o sensorPA.o sqlite3.o
	@echo "--- Criando o executavel: hospital_app ---"
	g++ -o hospital_app main.o database.o hospital.o paciente.o simulador.o sensor.o sensorSO.o sensorFC.o sensorFR.o sensorTC.o sensorPA.o sqlite3.o -pthread -ldl

main.o: main.cpp hospital.h database.h simulador.h
	g++ -c main.cpp -std=c++17 -pthread

database.o: database.cpp database.h sqlite3.h
	g++ -c database.cpp -std=c++17 -pthread

hospital.o: hospital.cpp hospital.h
	g++ -c hospital.cpp -std=c++17 -pthread

paciente.o: paciente.cpp paciente.h
	g++ -c paciente.cpp -std=c++17

simulador.o: simulador.cpp simulador.h
	g++ -c simulador.cpp -std=c++17 -pthread

sensor.o: sensor.cpp sensor.h
	g++ -c sensor.cpp -std=c++17

sensorSO.o: sensorSO.cpp sensorSO.h
	g++ -c sensorSO.cpp -std=c++17

sensorFC.o: sensorFC.cpp sensorFC.h
	g++ -c sensorFC.cpp -std=c++17

sensorFR.o: sensorFR.cpp sensorFR.h
	g++ -c sensorFR.cpp -std=c++17

sensorTC.o: sensorTC.cpp sensorTC.h
	g++ -c sensorTC.cpp -std=c++17

sensorPA.o: sensorPA.cpp sensorPA.h
	g++ -c sensorPA.cpp -std=c++17

sqlite3.o: sqlite3.c sqlite3.h
	gcc -c sqlite3.c -O2

clean:
	rm -f *.o hospital_app dados_hospital.db