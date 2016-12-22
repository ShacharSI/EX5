#**
#*Haim_Rubinstein Shachar_Sirotkin
#*203405386 208994962
#*EX1
#**/

a.out: main.o Searchable.o Bfs.o Map.o Square.o Point.o MapFactory.o Logic.o Algorithm.o Driver.o LuxTaxiFactory.o Taxi.o TaxiCenter.o Management.o LuxuryTaxi.o Passenger.o StandardTaxi.o StndTaxiFactory.o Validate_Interface.o Trip.o VirtualTaxiFactory.o
	g++ main.o Searchable.o Bfs.o MapFactory.o Map.o Square.o Point.o Logic.o Algorithm.o Driver.o LuxTaxiFactory.o Taxi.o TaxiCenter.o Management.o LuxuryTaxi.o Passenger.o StandardTaxi.o StndTaxiFactory.o Validate_Interface.o Trip.o VirtualTaxiFactory.o

main.o: main.cpp
	g++ -c main.cpp

Algorithm.o: Algorithm.cpp Algorithm.h 
	g++ -c Algorithm.cpp

Driver.o: Driver.cpp Driver.h 
	g++ -c Driver.cpp

LuxTaxiFactory.o: LuxTaxiFactory.cpp LuxTaxiFactory.h 
	g++ -c LuxTaxiFactory.cpp

Taxi.o: Taxi.cpp Taxi.h 
	g++ -c Taxi.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h 
	g++ -c TaxiCenter.cpp

Management.o: Management.cpp Management.h 
	g++ -c Management.cpp

LuxuryTaxi.o: LuxuryTaxi.cpp LuxuryTaxi.h 
	g++ -c LuxuryTaxi.cpp

Passenger.o: Passenger.cpp Passenger.h 
	g++ -c Passenger.cpp

StandardTaxi.o: StandardTaxi.cpp StandardTaxi.h 
	g++ -c StandardTaxi.cpp

StndTaxiFactor.o: StndTaxiFactory.cpp StndTaxiFactory.h 
	g++ -c StndTaxiFactory.cpp

Searchable.o: Searchable.cpp Searchable.h 
	g++ -c Searchable.cpp

MapFactory.o: MapFactory.cpp MapFactory.h 
	g++ -c MapFactory.cpp

Trip.o: Trip.cpp Trip.h 
	g++ -c Trip.cpp

Validate_Interface.o: Validate_Interface.cpp Validate_Interface.h 
	g++ -c Validate_Interface.cpp

VirtualTaxiFactory.o: VirtualTaxiFactory.cpp VirtualTaxiFactory.h 
	g++ -c VirtualTaxiFactory.cpp
	
Bfs.o: Bfs.cpp Bfs.h
	g++ -c Bfs.cpp

Square.o: Square.cpp Square.h
	g++ -c Square.cpp
	
Logic.o: Logic.cpp Logic.h
	g++ -c Logic.cpp
	
Map.o: Map.cpp Map.h
	g++ -c Map.cpp
	
Point.o: Point.cpp Point.h
	g++ -c Point.cpp
	
unzip:
	unzip ex1_p2.zip
