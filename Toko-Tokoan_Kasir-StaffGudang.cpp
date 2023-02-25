#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int banyakMBarang = 0;

int trcCount = 0;

struct masterBarang {
    char kodeBarang[120];
    char namaBarang[120];
    int harga;
    int stok;
} mBarang[100];

struct barang {
    char kodeBarang[120];
    int qty;
};

struct transaksi {
    int kodeTransaksi;
    char namaKasir[120];
    struct barang listBarang[120];
} listTransaksi[100];

int main();

int checkCode(char *kodeBarang) {

    for (int i = 0; i < 100; i++)
    {
        if(strcmp(kodeBarang, mBarang[i].kodeBarang) == 0) {
            return i;
        }
    }
    
    return -1;
}

int checkQty(int quantity, int id) {
    
    if (quantity <= mBarang[id].stok)
    {
        return 1;
    }
    
    return 0;
}

int addProduct(int productCount, int transactionCount) {
    char kodeProduk[120];
    int price;
    int quantity;
    int id;

    do
    {
        printf("Kode Produk: ");
        scanf("%[^\n]", kodeProduk);
        getchar();
		
		// making an id of the product
		id = checkCode(kodeProduk);
    } while (strlen(kodeProduk) < 1 || id == -1);

    strcpy(listTransaksi[transactionCount].listBarang[productCount].kodeBarang, kodeProduk);

//    printf("ID: %d\n", id);
//    printf("Item: %s\n", mBarang[id].namaBarang);
    
    do
    {
        printf("Jumlah Pembelian: ");
        scanf("%d", &quantity);
        getchar();
    } while (quantity < 1 && !checkQty(quantity, id));

    listTransaksi[transactionCount].listBarang[productCount].qty = quantity;
    
    mBarang[id].stok -= quantity;

    price = mBarang[id].harga * quantity;

    return price;
}

void addBarang() {
	system("cls");
	printf("\n\n");	
	printf("--MENU INPUT BARANG--\n\n");
    char namaBarang[120];
    int lenNamaBarang = 0;
    int hargaBarang = -1, stockBarang = -1;
    do {
        printf("Nama Barang [5-20 Karakter]: ");
        scanf("%[^\n]", namaBarang);
        getchar();
        lenNamaBarang = strlen(namaBarang);
    } while (lenNamaBarang > 20 || lenNamaBarang < 5);

    do {
        printf("Harga Barang [Rp 1.000,00 - Rp 1.000.000,00]: ");
        scanf("%d", &hargaBarang);
        scanf("%*[^\n]");
        getchar();
    } while (hargaBarang < 1000 || hargaBarang > 1000000);

    int switcher = 1;
    do {
        printf("Stock Barang [Berupa angka]: ");
        if (scanf("%d", &stockBarang) == 1) {
            switcher = 0;
        }
        scanf("%*[^\n]");
        getchar();
    } while (switcher == 1);
	
	char kode[200];
	sprintf(kode, "BIC%d", banyakMBarang+1);
	strcpy(mBarang[banyakMBarang].kodeBarang, kode);
	strcpy(mBarang[banyakMBarang].namaBarang, namaBarang);
	mBarang[banyakMBarang].harga = hargaBarang;
	mBarang[banyakMBarang].stok = stockBarang;

    printf("\nBarang berhasil diinput dengan kode produk %s\n", mBarang[banyakMBarang].kodeBarang);
    banyakMBarang++;
    printf("Enter to continue...");
    scanf("%*[^\n]");
    return;
}

void printBarang() {
	printf("============================================================================\n");
	printf("| No | Kode Barang |        Nama Barang      | Harga Barang | Stock Barang |\n");
	printf("============================================================================\n");
    for (int i = 0; i < banyakMBarang; i++) {
        printf("|%-3d |%-12s |%-24s |%-13d |%-14d|\n", i + 1, mBarang[i].kodeBarang, mBarang[i].namaBarang, mBarang[i].harga, mBarang[i].stok);
    }
    printf("============================================================================\n");
}

void lihatBarang(){
	printBarang();
	printf("Press enter to continue...");
}

void updateStock() {
	printf("\n\n");	
    int index;
    do {
        printf("Masukkan no [1-%d]: ", banyakMBarang);
        scanf("%d", &index);
        scanf("%*[^\n]");
        getchar();
    } while (index < 1 || index > banyakMBarang);

    int updateStock;
    printf("Stock yang mau diupdate: ");
    scanf("%d", &updateStock);
    scanf("%*[^\n]");
    getchar();

    mBarang[index - 1].stok = mBarang[index - 1].stok + updateStock;
    printf("\nStock barang %s berhasil diupdate\n", mBarang[index - 1].namaBarang);
    printf("Press enter to continue...");
}

void staffGudang(){
	int pilihan = 0;
	do {
        system("cls");
        printf("\n\n");	
    	puts("	STAFF GUDANG");
		printf("\n");
        puts("	1. Input Barang");
        puts("	2. Lihat Barang");
        puts("	3. Update Stock");
        puts("	4. Kembali");
		
		pilihan = 0;
        do {
            printf("	Masukkan pilihan [1-3]: ");
            scanf("%d", &pilihan);
            scanf("%*[^\n]");
            getchar();
        } while (pilihan < 1 || pilihan > 4);

        if (pilihan == 1) {
            addBarang();
        } 
		else if(pilihan == 2){
        	system("cls");
        	printf("\n\n");	
			printf("--MENU LIHAT BARANG--\n\n");
			if (banyakMBarang == 0) {
                printf("Data barang kosong");
            } else {
                lihatBarang();
            }
        	
		}
		else if (pilihan == 3) {
        	system("cls");
            printf("\n\n");	
			printf("--MENU UPDATE BARANG--\n\n");
            if (banyakMBarang == 0) {
                printf("Data barang kosong");
            } else {
                printBarang();
                updateStock();
            }
        } 
		else if (pilihan == 4) {
            main();
        }
        getchar();
    } while (pilihan != 4);
}

void addTransaksi(int transCount) {
    char namaKasir[120];
    char choose;
    int prdCount = 0;
    int totalPrice = 0;

    do
    {
        printf("Nama Kasir [5-20 karakter]: ");
        scanf("%[^\n]", namaKasir);
        getchar();
    } while (strlen(namaKasir) > 20 || strlen(namaKasir) < 5);

    strcpy(listTransaksi[transCount].namaKasir, namaKasir);
    
    do
    {
        totalPrice += addProduct(prdCount, transCount);
        prdCount++;
        printf("Apakah ingin menambah produk pada transaksi?\n");
        printf("Choose Y/N (Case Sensitive)\n");
        printf("Y/N: ");
        scanf("%c", &choose);
        getchar();
    } while (choose == 'Y' || choose == 'y');

    listTransaksi[transCount].kodeTransaksi = (transCount + 1);

    printf("Total Transaksi TK%d adalah Rp %d\n", transCount + 1, totalPrice);
    printf("Press enter to continue...");

}


void showTransaction(int transCount) {
    if (transCount == 0)
    {
        printf("Tidak Ada Transaksi\n");
        printf("Press enter to continue...");
//        getchar();
        return;
    }
        printf("============================================================================================================================\n");
		printf("| No | Kode Transaksi |        Nama Kasir      | Total Harga |                      Deskripsi Barang                       |\n");
		printf("============================================================================================================================\n");

    for (int i = 0; i < transCount; i++)
    {
        char namaKasir[120];
        char kodeProduk[120][120];
        char product[120][120];
        strcpy(namaKasir, listTransaksi[i].namaKasir);
        int quantity[120];
        int price[120]; 
        int totalPrice = 0;
        

        for (int j = 0; j < 120; j++)
        {
            if (listTransaksi[i].listBarang[j].qty == NULL)
            {
                break;
            }
            
            strcpy(kodeProduk[j], listTransaksi[i].listBarang[j].kodeBarang);
            int id = checkCode(kodeProduk[j]);
            strcpy(product[j], mBarang[id].namaBarang);
            quantity[j] = listTransaksi[i].listBarang[j].qty;
            price[j] = mBarang[id].harga;
            totalPrice += price[j];
        }

        
        printf("| %-2d | TX%d            | %-22s | Rp.%8d |", i + 1, i + 1, namaKasir, totalPrice);
        
        for (int j = 0; j < 120; j++)
        {
            if (listTransaksi[i].listBarang[j].qty == NULL)
            {
                break;
            }

            if (j > 0)
            {
                printf("|%*c|%*c|%*c|%*c|", 4, ' ', 16, ' ', 24, ' ', 13, ' ');
            }
            
            printf(" %2d. %4s - %16s - %5d pcs - Rp.%-15d|\n", j + 1, kodeProduk[j], product[j], quantity[j], price[j]);
        }

        printf("============================================================================================================================\n");
        
    }
	printf("\nPress enter to continue...");
    return;
    
    
}

void kasirMenu(){
	int pilihan;

	do{
		system("cls");
		printf("\n\n");	
    	puts("	KASIR");
		printf("\n");
		puts("	1. Menambah Transaksi");
		puts("	2. List Transaksi");
		puts("	3. Kembali");
		
		
		do{
			printf("	Masukkan pilihan [1-3]: ");
			scanf("%d", &pilihan);
			scanf("%[^\n]");
			getchar();
		}while(pilihan<1 || pilihan>3);
		
		if(pilihan==1){
			system("cls");
			printf("\n\n--Menu input Transaksi--\n\n");
			addTransaksi(trcCount);
            trcCount++;
		}
		else if(pilihan == 2){
			system("cls");
			printf("\n\n--Transaction Data--\n\n");
			showTransaction(trcCount);
		}
		else if(pilihan == 3){
			main();
		}
		getchar();
	}while(pilihan !=3);

}

void exit(){
	system("cls");
	printf("\n\nNAMA :\n");
	printf("1. Jennifer Ardelia Limicia - 2602105090\n");
	printf("2. Solascriptura Bintang Sulaiman - 2602167675\n");
	printf("3. Wilbert Chandra - 2602113666\n");
	printf("Kelas : LB-09\n\n");
	printf("Babai~~~\n");
}

int main() {
    int pilihan = 0;
    
    do{
    	pilihan = 0;
    	system("cls");
    	printf("\n\n");	
    	puts("	TOKO-TOKOAN");
		printf("\n");
    	puts("	1. Staff Gudang");
    	puts("	2. Kasir");
    	puts("	3. Exit");
    	
    	do {
            printf("	Masukkan pilihan role [1-3]: ");
            scanf("%d", &pilihan);
            scanf("%*[^\n]");
            getchar();
        } while (pilihan < 1 || pilihan > 3);
    	
    	switch (pilihan){
    		case 1:
    			staffGudang();
    		case 2:
    			kasirMenu();
		}
		
		if(pilihan == 3){
			exit(0);
		}
	}while(true);
    
    return 0;
}
