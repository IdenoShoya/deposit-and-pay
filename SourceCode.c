/*氏名：出野翔也
  所属：名城大学 理工学部 情報工学科 2年
  目的：ユーザーの個人情報を入力して、そのユーザーの口座を生成し、預金、支払いを行い、ユーザー側から終了するよう入力することで終了する。*/
#include<stdio.h>

//ユーザー情報を格納するための構造体
struct User {
	char l_name[10]; //家族名(last name)
	char name[10]; //名前
	char sex; //性別
	int age; //年齢
	int cash; //残高
};
//関数を事前に定義する
void showingUser(struct User user);
void paying(struct User *user, int pay);
void depositing(struct User *user, int amo);
void showDeposit(struct User *user);

/*メイン関数*/
int main(void) {
	
	struct User user; //口座生成
	int move = 0; //モード変更用の変数
	int money; //入出金額を格納しておくための変数
	char dummy; //入力を正常に行うために、間に挟む変数

	//氏名入力を行う
	printf("姓を入力してください：");
	scanf_s("%s", user.l_name, 10);
	printf("名を入力してください：");
	scanf_s("%s", user.name, 10);

	//性別が規定のもので入力されるまでループする
	while (1) {
		printf("性別を男性、女性、その他をそれぞれM、F、Oで入力してください：");
		scanf("%c", &dummy); //改行文字を入力に入れないためのダミー文字入力
		scanf("%c", &user.sex); //性別を判別するための一文字を入力
		//規定したものか判別する
		if ('M' == user.sex || 'F' == user.sex || 'O' == user.sex) {
			break; //ループ判別
		}
		//入力が間違っていた場合
		else {
			printf("入力が間違っている可能性があります。もう一度お願いします。\n"); //間違っていた旨を出力し、ループ継続
			continue;
		}
	}

	//年齢を入力する
	printf("年齢を入力してください：");
	scanf("%d", &user.age);

	//残高を1000円に設定
	user.cash = 1000;
	printf("ユーザー作成を行っていただけたため、初期残高として1000円に設定させていただきます！\n");

	showingUser(user); //設定したユーザー情報を出力する

	//モード分類の解説
	printf("\n支払いの場合は0\n預金の場合は1\n残高確認の場合は2\nユーザー情報を表示する場合は3\n終了の場合は上記以外の数字を入力してください\n");
	/*終了が入力されるまでループする*/
	while (1) {
		//モードの入力を行う
		printf("\nモード入力：");
		scanf("%d", &move);
		
		//支払いモード
		if (move == 0) {
			printf("支払額を入力してください：");
			scanf("%d", &money);
			paying(&user, money);
		}
		//預金モード
		else if (move == 1) {
			printf("預金額を入力してください：");
			scanf("%d", &money);
			depositing(&user, money);
		}
		//残高表示モード
		else if (move == 2) {
			printf("残高表示を行います\n");
			showDeposit(&user);
		}
		//ユーザー情報表示モード
		else if (move == 3) {
			showingUser(user);
		}
		 //ループの終了
		else {
			//ループ脱出
			break;
		}
	}
	printf("\n処理を終了します...\n");

	return 0; //終わり
}

/*ユーザー情報を表示する関数*/
void showingUser(struct User user) {
	printf("\nユーザー情報の表示を行います...\n");
	printf("氏名：%s %s\n", user.l_name, user.name);
	printf("性別：");
	//性別の文字によって判別するスイッチ文
	switch (user.sex) {
	case 'M':
		printf("男性\n");
		break;
	case 'F':
		printf("女性\n");
		break;
	case 'O':
		printf("その他\n");
		break;
	default:
		printf("表示できません\n");
		break;
	}
	printf("年齢：%d\n", user.age);
	printf("預金残高：%d円\n", user.cash);
}

/*支払い諸々の関数*/
void paying(struct User *user, int pay) {
	//支払い可能か判別する
	if (pay <= user->cash) { //支払い可能
		printf("%d円の支払いを行います\n", pay);
		user->cash -= pay;
		printf("支払いが完了しました\n");
	}
	else { //支払い不可
		printf("支払額が残高を越えているため、処理を中止しました\n");
	}
	//残高表示をする
	showDeposit(user);
}

/*預金をするための関数*/
void depositing(struct User *user, int amo) {
	printf("%d円の預金を行います\n", amo);
	user->cash += amo;
	printf("預金が完了しました\n");
	//残高表示
	showDeposit(user);
}

/*残高表示用の関数*/
void showDeposit(struct User *user) {
	printf("預金残高：%d円\n", user->cash);
}