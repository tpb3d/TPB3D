#pragma once
#include <string.h>

//People/Locations.h
//defines the default locations for parks and peep homes/backgrounds
#define useLocationEnum 1
#if useLocationEnum
	typedef enum{
		locIndexWorld	=	0	,
		locIndexAngloNorthAmerica	=	1	,
		locIndexUnitedStates	=	2	,
		locIndexNewEngland	=	3	,
		locIndexConnecticut	=	4	,
		locIndexRhodeIsland	=	5	,
		locIndexMassachusetts	=	6	,
		locIndexMaine	=	7	,
		locIndexNewHampshire	=	8	,
		locIndexVermont	=	9	,
		locIndexMegalopolisUsa	=	10	,
		locIndexNewYork	=	11	,
		locIndexNewJersey	=	12	,
		locIndexMaryland	=	13	,
		locIndexPennsylvania	=	14	,
		locIndexDc	=	15	,
		locIndexDelaware	=	16	,
		locIndexSouthAtlanticUsa	=	17	,
		locIndexPuertoRico	=	18	,
		locIndexFlorida	=	19	,
		locIndexGeorgiaUsa	=	20	,
		locIndexNorthCarolina	=	21	,
		locIndexSouthCarolina	=	22	,
		locIndexVirginia	=	23	,
		locIndexWestVirginia	=	24	,
		locIndexDixie	=	25	,
		locIndexAlabama	=	26	,
		locIndexLouisiana	=	27	,
		locIndexKentucky	=	28	,
		locIndexTennessee	=	29	,
		locIndexMississippi	=	30	,
		locIndexArkansas	=	31	,
		locIndexGreatLakesUsa	=	32	,
		locIndexIllinois	=	33	,
		locIndexMichigan	=	34	,
		locIndexOhio	=	35	,
		locIndexIndiana	=	36	,
		locIndexWisconsin	=	37	,
		locIndexMinnesota	=	38	,
		locIndexGreatPlainsUsa	=	39	,
		locIndexKansas	=	40	,
		locIndexNebraska	=	41	,
		locIndexNorthDakota	=	42	,
		locIndexSouthDakota	=	43	,
		locIndexIowa	=	44	,
		locIndexMissouri	=	45	,
		locIndexSouthwestUsa	=	46	,
		locIndexTexas	=	47	,
		locIndexOklahoma	=	48	,
		locIndexNewMexico	=	49	,
		locIndexArizona	=	50	,
		locIndexMountainsUsa	=	51	,
		locIndexUtah	=	52	,
		locIndexColorado	=	53	,
		locIndexWyoming	=	54	,
		locIndexMontana	=	55	,
		locIndexIdaho	=	56	,
		locIndexPacificUsa	=	57	,
		locIndexCalifornia	=	58	,
		locIndexWashington	=	59	,
		locIndexOregon	=	60	,
		locIndexHawaii	=	61	,
		locIndexCanada	=	62	,
		locIndexWestCn	=	63	,
		locIndexBritishColumbia	=	64	,
		locIndexAlberta	=	65	,
		locIndexManitoba	=	66	,
		locIndexSaskatchewan	=	67	,
		locIndexYukon	=	68	,
		locIndexNunavut	=	69	,
		locIndexEastCn	=	70	,
		locIndexOntario	=	71	,
		locIndexQuebec	=	72	,
		locIndexNovaScotia	=	73	,
		locIndexNewfoundland	=	74	,
		locIndexPrinceEdwardIsland	=	75	,
		locIndexNewBrunswick	=	76	,
		locIndexLatinAmerica	=	77	,
		locIndexCaribbean	=	78	,
		locIndexWestCarib	=	79	,
		locIndexCuba	=	80	,
		locIndexJamaica	=	81	,
		locIndexHaiti	=	82	,
		locIndexDominicanRepublic	=	83	,
		locIndexUsVirginIslands	=	84	,
		locIndexBritishVirginIslands	=	85	,
		locIndexBahamas	=	86	,
		locIndexCaymanIslands	=	87	,
		locIndexTurksAndCaicosIslands	=	88	,
		locIndexEastCarib	=	89	,
		locIndexAntigua	=	90	,
		locIndexBarbuda	=	91	,
		locIndexNetherlandsAntilles	=	92	,
		locIndexDominica	=	93	,
		locIndexNevis	=	94	,
		locIndexStKitts	=	95	,
		locIndexGrenada	=	96	,
		locIndexStVincentAndGrenadines	=	97	,
		locIndexAnguilla	=	98	,
		locIndexStLucia	=	99	,
		locIndexGuadeloupe	=	100	,
		locIndexTrinidadAndTobago	=	101	,
		locIndexStMartin	=	102	,
		locIndexSaintBarthelemy	=	103	,
		locIndexNorthSlashCentralAmerica	=	104	,
		locIndexMexico	=	105	,
		locIndexBelize	=	106	,
		locIndexCostaRica	=	107	,
		locIndexElSalvador	=	108	,
		locIndexGuatemala	=	109	,
		locIndexHonduras	=	110	,
		locIndexNicaragua	=	111	,
		locIndexPanama	=	112	,
		locIndexSouthAmerica	=	113	,
		locIndexBrazil	=	114	,
		locIndexBolivia	=	115	,
		//locIndexBrazil	=	116	,
		locIndexChile	=	117	,
		locIndexColombia	=	118	,
		locIndexEcuador	=	119	,
		locIndexFalklandIslands	=	120	,
		locIndexFrenchGuiana	=	121	,
		locIndexParaguay	=	122	,
		locIndexPeru	=	123	,
		locIndexSandwichIslandsAndS	=	124	,
		locIndexSuriname	=	125	,
		locIndexUruguay	=	126	,
		locIndexVenezuela	=	127	,
		locIndexEurope	=	128	,
		locIndexBritishIsles	=	129	,
		locIndexIreland	=	130	,
		locIndexWales	=	131	,
		locIndexEngland	=	132	,
		locIndexScotland	=	133	,
		locIndexScandinavian	=	134	,
		locIndexSweden	=	135	,
		locIndexDenmark	=	136	,
		locIndexIceland	=	137	,
		locIndexNorway	=	138	,
		locIndexFinland	=	139	,
		locIndexGreenland	=	140	,
		locIndexWestcentralEur	=	141	,
		locIndexNetherlands	=	142	,
		locIndexBelgium	=	143	,
		locIndexGermany	=	144	,
		locIndexSwitzerland	=	145	,
		locIndexAustria	=	146	,
		locIndexCzechRepublic	=	147	,
		locIndexRomance	=	148	,
		locIndexSpain	=	149	,
		locIndexFrance	=	150	,
		locIndexPortugal	=	151	,
		locIndexItaly	=	152	,
		locIndexRomania	=	153	,
		locIndexEasternEur	=	154	,
		locIndexLithuania	=	155	,
		locIndexLatvia	=	156	,
		locIndexEstonia	=	157	,
		locIndexRussia	=	158	,
		locIndexPoland	=	159	,
		locIndexUkraine	=	160	,
		locIndexBelarus	=	161	,
		locIndexMoldova	=	162	,
		locIndexAdriatic	=	163	,
		locIndexSlovenia	=	164	,
		locIndexBosniaAndHerzagovina	=	165	,
		locIndexMontenegro	=	166	,
		locIndexCroatia	=	167	,
		locIndexHungary	=	168	,
		locIndexSerbia	=	169	,
		locIndexSoutheasternEur	=	170	,
		locIndexGreece	=	171	,
		locIndexMacedonia	=	172	,
		locIndexAlbania	=	173	,
		locIndexBulgaria	=	174	,
		locIndexArabWorld	=	175	,
		locIndexNorthAfrica	=	176	,
		locIndexHorn	=	177	,
		locIndexSomalia	=	178	,
		locIndexDjibouti	=	179	,
		locIndexEritrea	=	180	,
		locIndexSudan	=	181	,
		locIndexMediterraneanPlusSaharan	=	182	,
		locIndexAlgeria	=	183	,
		locIndexTunisia	=	184	,
		locIndexLibya	=	185	,
		locIndexEgypt	=	186	,
		locIndexChad	=	187	,
		locIndexAtlanticArab	=	188	,
		locIndexMorocco	=	189	,
		locIndexWesternSahara	=	190	,
		locIndexMauritania	=	191	,
		locIndexMiddleEast	=	192	,
		locIndexArabianPeninsula	=	193	,
		locIndexYemen	=	194	,
		locIndexOman	=	195	,
		locIndexSaudiArabia	=	196	,
		locIndexUnitedArabEmirates	=	197	,
		locIndexQatar	=	198	,
		locIndexKuwait	=	199	,
		locIndexCrescentCrossroads	=	200	,
		locIndexIraq	=	201	,
		locIndexJordan	=	202	,
		locIndexLebanon	=	203	,
		locIndexSyria	=	204	,
		locIndexIsrael	=	205	,
		locIndexAfrica	=	206	,
		locIndexEasternAfr	=	207	,
		locIndexEthiopia	=	208	,
		locIndexKenya	=	209	,
		locIndexTanzania	=	210	,
		locIndexMadagascar	=	211	,
		locIndexUganda	=	212	,
		locIndexRwanda	=	213	,
		locIndexBurundi	=	214	,
		locIndexReunion	=	215	,
		locIndexMauritius	=	216	,
		locIndexMalawi	=	217	,
		locIndexMiddleAfr	=	218	,
		locIndexCentralAfricanRepublic	=	219	,
		locIndexCongo	=	220	,
		locIndexDRCongo	=	221	,
		locIndexZambia	=	222	,
		locIndexCameroon	=	223	,
		//locIndexCongo	=	224	,
		locIndexEquatorialGuinea	=	225	,
		locIndexGabon	=	226	,
		locIndexSaoTomeAndPrincipe	=	227	,
		locIndexWesternAfr	=	228	,
		locIndexAtlanticAfr	=	229	,
		locIndexGambia	=	230	,
		locIndexGuinea	=	231	,
		locIndexCapeVerde	=	232	,
		locIndexSenegal	=	233	,
		locIndexSierraLeone	=	234	,
		locIndexLiberia	=	235	,
		locIndexWestCentralAfr	=	236	,
		locIndexNigeria	=	237	,
		locIndexNiger	=	238	,
		locIndexGhana	=	239	,
		locIndexMali	=	240	,
		locIndexBurkinaFaso	=	241	,
		locIndexTogo	=	242	,
		locIndexIvoryCoast	=	243	,
		locIndexSouthernAfr	=	244	,
		locIndexSouthAfrica	=	245	,
		locIndexBotswana	=	246	,
		locIndexNamibia	=	247	,
		locIndexSwaziland	=	248	,
		locIndexLesotho	=	249	,
		locIndexZimbabwe	=	250	,
		locIndexSilkRoad	=	251	,
		locIndexMountainsAndSeasSilk	=	252	,
		locIndexTurkey	=	253	,
		locIndexGeorgia	=	254	,
		locIndexArmenia	=	255	,
		locIndexAzerbaijan	=	256	,
		locIndexIran	=	257	,
		locIndexStansCentralAsian	=	258	,
		locIndexAfghanistan	=	259	,
		locIndexTurkmenistan	=	260	,
		locIndexUzbekistan	=	261	,
		locIndexTajikistan	=	262	,
		locIndexKyrgyzstan	=	263	,
		locIndexKazakhstan	=	264	,
		locIndexSouthAsia	=	265	,
		locIndexIndianSubcontinent	=	266	,
		locIndexIndia	=	267	,
		locIndexPakistan	=	268	,
		locIndexSriLanka	=	269	,
		locIndexNepal	=	270	,
		locIndexBangladesh	=	271	,
		locIndexBhutan	=	272	,
		locIndexSoutheastAsia	=	273	,
		locIndexBurma	=	274	,
		locIndexThailand	=	275	,
		locIndexCambodia	=	276	,
		locIndexLaos	=	277	,
		locIndexVietnam	=	278	,
		locIndexPhilipines	=	279	,
		locIndexMalaysia	=	280	,
		locIndexIndonesia	=	281	,
		locIndexFarEast	=	282	,
		locIndexMainlandFarEast	=	283	,
		locIndexChina	=	284	,
		locIndexNorthKorea	=	285	,
		locIndexSouthKorea	=	286	,
		locIndexMongolia	=	287	,
		locIndexIslandsFarEast	=	288	,
		locIndexJapan	=	289	,
		locIndexTaiwan	=	290	,
		locIndexGuam	=	291	,
		locIndexOceania	=	292	,
		locIndexBritishOceania	=	293	,
		locIndexAustralia	=	294	,
		locIndexNewZealand	=	295	,
		locIndexTasmania	=	296	,
		locIndexMelanesia	=	297	,
		locIndexFiji	=	298	,
		locIndexPapauNewGuinea	=	299	,
		locIndexNewCaledonia	=	300	,
		locIndexVanuatu	=	301	,
		locIndexPolynesia	=	302	,
		locIndexWesternSamoa	=	303	,
		locIndexAmericanSamoa	=	304	,
		locIndexTonga	=	305	,
		locIndexPitcairn	=	306	,
		locIndexFrenchPolynesia	=	307	,
		locIndexEasterIsland	=	308	,
		locIndexTuvalu	=	309	,
		locIndexCookIslands	=	310	,
		locIndexOtherJustForFun	=	311	,
		locIndexAlienPlanets	=	312	,
		locIndexMarsPlanet	=	313	,
		}WorldLocationIndices;
#else
#endif

const short locIndexRoot=locIndexWorld;
const short locIndexFirstCustom	=	locIndexMarsPlanet+1;
const short nWorldLocationIndices=500; //save some room for custom locations
const short locNoParent	=-1;
const short locNoSublevel	=0;
const short loctextMaxChars	=	48-4;

struct Location{
	short parentindex;
	union	{
		unsigned short allLevels;
		struct{unsigned long l1:4,l2:4,l3:4,l4:4,l5:4;}	levels;
		};
	char loctext[loctextMaxChars];
	//Init: constructor method that can be called
	void Init(short sparenti,short sl1,short sl2,short sl3,short sl4,short sl5,char*sloctext){
		parentindex=sparenti;
		#define l(a)	levels.l##a=sl##a
		l(1);	l(2);	l(3);	l(4);	l(5);
		#undef l
		strncpy(loctext,sloctext,loctextMaxChars-1);
		}
	Location(short sparenti,short l1,short l2,short l3,short l4,short l5,char*sloctext){
		Init(sparenti,l1,l2,l3,l4,l5,sloctext);
		}
	Location(){
		Init(locNoParent,locNoSublevel,locNoSublevel,locNoSublevel,locNoSublevel,locNoSublevel,"");
		}
	//Location operator=(Location b){	memcpy(this,&b,sizeof(Location));	return(*this);};
	};//struct Location;


//this initialization may have to be moved to the cpp file or into a LocationInit() function

class WorldLocations{
	public:
	short nlocations;
	Location locations[nWorldLocationIndices];
	WorldLocations();
	};

class LocationLineageString	{
	public:
	#define loclineageStringBufferSize 0x100
	#define locseparatorStringSize 8
	WorldLocations*wloc;
	char sep[locseparatorStringSize];
	char bufr[loclineageStringBufferSize];
	inline int Len(){	return (int)strlen(bufr);	}
	//unary suffix operator !: length of string
	inline int operator!(){	this->Len();	}
	inline int MaxCatLen(){	return(loclineageStringBufferSize-Len());	}
	inline void CleanBufr(){	memset(bufr,0,loclineageStringBufferSize);	}
	inline void CleanSep(){	memset(sep,0,locseparatorStringSize);	}
	void CleanStrings(){	CleanBufr();	CleanSep();	}
	void SetSep(char*ssep){
		CleanSep();	strncpy(sep,ssep,locseparatorStringSize-1);
		}
	LocationLineageString(WorldLocations*swloc,char*ssep)	{
		wloc=swloc;				CleanStrings();
		}
	inline void SepCat(){	Cat(sep);	}
	inline void Cat(char*s){	Append(s);	}
	void Append(char*s){
		strncat(bufr,sep,MaxCatLen());
		strncat(bufr,s,MaxCatLen());
		}
	void Prepend(char*s){
		char tbufr[loclineageStringBufferSize];
		strcpy(tbufr,bufr);		strncpy(bufr,s,loclineageStringBufferSize-1);
		strncat(bufr,tbufr,loclineageStringBufferSize-Len()-1);
		}
	//operator >>:	append with predefined separator
	void operator>>(char*s){	if(Len())	{	SepCat();	}	Append(s);	}
	//operator <<:	prepend with predefined separator
	void operator<<(char*s){	if(Len())	{	Prepend(sep);	}	Prepend(s);	}
	//
	char*BuildLineageString(short location,char*ssep){
		short l=location;
		CleanBufr();	SetSep(ssep);
		while(l<wloc->nlocations&&l!=wloc->locations[l].parentindex){
			*this<<wloc->locations[l].loctext;
			l=wloc->locations[l].parentindex;
			}
		if(l==locIndexRoot){	//root
			*this<<wloc->locations[l].loctext;
			}
		return(&bufr[0]);
		}//BuildLineageString()
	};
