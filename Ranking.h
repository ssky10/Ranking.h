/////////////////////////////////////////////////////////////////////////////////////////////////////
// 이름 : Ranking.h                                                                                //
// 목적 : 랭킹시스템을 손쉽게 구축하기 위한 헤더파일                                               //
// 구조체 : Ranking_system(약자 Ranker) - 원하는 순위 만큼 배열선언                                //
//          멤버 : int형 rank(랭킹점수)                                                            //
//                 char형 nickname(랭커의 이름)                                                    //
//                    - 특징 : 영문자,숫자 : 998자                                                 //
//                             한글 : 499자                                                        //
// - 매개변수 설명 -                                                                               //
// char형 *file_name : 파일명에 해당하는 문자열(확장자 포함해서)                                   //
// Ranker형 *rankers[] : 랭킹배열의 포인터값                                                       //
// int형 Rank_num : 랭킹배열의 길이                                                                //
//                  (예를들어,10위까지 저장할경우 10)                                              //
// int형 password : 랭킹파일 초기화시 설정할 비밀번호                                              //
// char형 select : 점수를 오름차순으로 매길경우 1                                                  //
//                 점수를 내림차순으로 매길경우 0                                                  //
// int형 user_score : 유저의 게임결과점수                                                          //
// char형 *user_name : 유저의 닉네임                                                               //
//                                                                                                 //
// - 함수 설명 -                                                                                   //
// int ranker_R(char *file_name, Ranker *rankers[], int Rank_num)                                  //
// :랭킹파일을 읽어오면서 랭킹파일에 저장된 내용을 랭킹배열에 저장                                 //
//  (랭킹파일이 정상적으로 열린경우 0반환, 아닌경우 -1반환)                                        //
// int ranker_reset(char *file_name, int Rank_num, int password, char select)                      //
// :랭킹파일을 리셋하는 함수                                                                       //
//  (비밀번호를 올바로 입력받았을경우 0반환,아닐경우 -1반환)                                       //
// void ranker_see(Ranker *rankers[], int Rank_num)                                                //
// :랭킹배열에 저장된 정보 화면에 출력(콘솔창 정리는 미포함)                                       //
// void ranker_save(char *file_name, Ranker *rankers[], int Rank_num)                              //
// :랭킹배열에 저장된 정보를 랭킹파일로 저장                                                       //
// int ranker_cheak(int user_score, char *user_name, Ranker *rankers[], int Rank_num, char select) //
// :게임결과를 전달하면 랭킹배열과 비교하여 랭킹에 포함될 경우 랭킹배열에 알맞는 위치에 저장하고   //
//  순위를 반환, 순위권이 아니면 -1                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Ranking_system
{
	int rank;
	char nickname[999];
} Ranker;

int ranker_R(char *file_name,Ranker *rankers,int Rank_num)
{
	FILE *fp;
	int i=0;

	fp = fopen(file_name,"r");

	if(fp == NULL)		
		return -1;
	else
		printf("실행중!!");	
	
	for(i=0;i<Rank_num;i++){
		fscanf(fp,"%d  %s",&((rankers+i)->rank),(rankers+i)->nickname);
	}
	fclose(fp);

	return 0;
}

int ranker_reset(char *file_name,int Rank_num,int password, char select)
{
	FILE *fp;
	int A;
	time_t ti1;
	struct tm *time1;
	time(&ti1);
	time1 = localtime(&ti1);

	system("cls");
	printf("비밀번호를 입력하세요:");
	scanf("%d",&A);
	if(A==password){
		fp = fopen(file_name,"w");
		for(A=0;A<Rank_num;A++){
			if(select==1)
				fprintf(fp,"9999  기록없음\n");
			else
				fprintf(fp,"0  기록없음\n");
		}
		fprintf(fp,"%d년 %d월 %d일 %d시 %d분 %d초에 마지막 초기화",time1->tm_year+1900,time1->tm_mon+1,time1->tm_mday,time1->tm_hour,time1->tm_min,time1->tm_sec);
		fclose(fp);
		//printf("성공적으로 초기화 되었습니다.");
		//Sleep(2000);
		return 0;
	}else{
		//printf("잘못된비밀번호입니다.");
		//Sleep(2000);
		return -1;
	}
}

void ranker_see(Ranker *rankers,int Rank_num)
{
	int i;

	printf("현재 랭킹\n");
	printf("----------------------일반 모드----------------------\n");
	for(i=0;i<Rank_num;i++){
		printf("%d위   %d초   %s\n",i+1,(rankers+i)->rank,(rankers+i)->nickname);
	}
}

void ranker_save(char *file_name,Ranker *rankers,int Rank_num)
{
	FILE *fp;
	int i;

	fp = fopen(file_name,"w");
	for(i=0;i<Rank_num;i++){
		fprintf(fp,"%d  %s\n",(rankers+i)->rank,(rankers+i)->nickname);
	}
	fclose(fp);
}

int ranker_cheak(int user_score,char *user_name,Ranker *rankers,int Rank_num, char select)
{
	int a,i;
	
	if(select==1){
		if((rankers+(Rank_num-1))->rank<=user_score) return -1;
		for(a=0; a<Rank_num; a++){
			if(((rankers+a)->rank)>user_score){
				for(i=Rank_num-1;i>a;i--){
					(rankers+i)->rank = (rankers+i-1)->rank;
					strcpy((rankers+i)->nickname,(rankers+i-1)->nickname);
				}
				(rankers+a)->rank = user_score;
				strcpy((rankers+a)->nickname,user_name);
				return (a+1);
			}
		}
	}else{
		if((rankers+(Rank_num-1))->rank>=user_score) return -1;
		for(a=0; a<Rank_num; a++){
			if(((rankers+a)->rank)<user_score){
				for(i=Rank_num-1;i>a;i--){
					(rankers+i)->rank = (rankers+i-1)->rank;
					strcpy((rankers+i)->nickname,(rankers+i-1)->nickname);
				}
				(rankers+a)->rank = user_score;
				strcpy((rankers+a)->nickname,user_name);
				return (a+1);
			}
		}
	}
}
