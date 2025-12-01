#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

int size = 6;       
int transCount = 0; 

struct Product{
    char productId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
};

struct Transaction{
    char productId[10];
    char type[10]; 
    int qty;
    char date[20];
};

void trimSpace(char *str){
	char *start = str;
    while(*start && isspace(*start)){
    	start++;
	} 
    char *end = start + strlen(start) - 1;
    while(end >= start && isspace(*end)){
    	end--;
	}
    *(end + 1) = '\0';
    if (start != str){
        memmove(str, start, strlen(start) + 1);
    }
}

void toLowerStr(char *str){
    int i;
    for(i=0;str[i];i++){
        str[i] = tolower(str[i]);
    }
}

void getCurrentDate(char *buffer){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int isDuplicateID(struct Product product[], char id[]){
    int i;
    for(i=0; i<size; i++){
        if (strcmp(product[i].productId, id) == 0){
            return 1;
        }
    }
    return 0;
}

  int luaChon(int min, int max) {
    char buffer[50];
    int value;
    do {
        printf("Lua chon cua ban(%d - %d): ", min, max);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        buffer[strcspn(buffer,"\n")] = '\0';
//        trimSpace(buffer);
        if (buffer[0]=='\0'||buffer[0]==' ') {
            printf("Lua chon khong duoc de trong\n");
        } else {
            int isNumber = 1;
            for (int i = 0; i < strlen(buffer); i++) {
                if (!isdigit(buffer[i])) {
                    isNumber = 0;
                    break;
                }
            }
            if (isNumber) {
                value = atoi(buffer);
                if (value >= min && value <= max) {
                    return value;
                } else {
                    printf("Vui long chon tu %d den %d\n", min, max);
                }
            } else {
                printf("Vui long nhap so nguyen\n");
            }
        }
    } while(1);
}

int themSanPham(int min, int max){
    char buffer[50];
    int value;
    do {
        printf("them so san pham: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        	continue;
		}
        buffer[strcspn(buffer,"\n")] = '\0';
        trimSpace(buffer);
        if(buffer[0]=='\0'||buffer[0]==' '){
            printf("Lua chon khong duoc de trong\n");
        }else {
            int isNumber = 1;
            for (int i = 0; i < strlen(buffer); i++) {
                if (!isdigit(buffer[i])) {
                    isNumber = 0;
                    break;
                }
            }
            if (isNumber){
                value = atoi(buffer);
                if (value >= min && value <= max) {
                    return value;
                }else if(value<min){
                    printf("Vui long nhap so luong >=0\n");
				}
            }else {
                printf("Vui long nhap so nguyen\n");
            }
        }
    } while(value+size<=36);
}

int nhapSoluong(int min) {
    char buffer[50];
    int value;
	int exit=0;
    do {
        printf("Nhap so luong san pham: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL){
			continue;
		}
        buffer[strcspn(buffer,"\n")] = '\0';
        trimSpace(buffer);
        if(buffer[0]=='\0'||buffer[0]==' '){
            printf("Lua chon khong duoc de trong\n");
        }else{
            int isNumber = 1;
            for(int i = 0; i < strlen(buffer); i++){
                if(!isdigit(buffer[i])){
                    isNumber = 0;
                    break;
                }
            }
            if(isNumber){
            	value = atoi(buffer);
                if(value >= min){
                    return value;
                }else if(value<min){
                    printf("Vui long nhap so luong >=0\n", min);
				}
            }else{
                printf("Vui long nhap so nguyen duong\n");
            }
    	}   
	}while(1);
}

void mainMenu(){
    printf("\n************** MENU *************\n");
    printf("1. Quan ly san pham\n");
    printf("2. Quan ly giao dich\n");
    printf("3. Thoat\n");
    printf("*********************************\n");
}

void productMenu(){
    printf("\n*********** PRODUCT ***********\n");
    printf("1. Them mat hang moi\n");
    printf("2. Cap nhat thong tin\n");
    printf("3. Quan ly trang thai\n");
    printf("4. Tim kiem hang hoa\n");
    printf("5. Danh sach hang hoa\n");
    printf("6. Sap xep danh sach\n");
    printf("7. Quay lai\n");
    printf("*******************************\n");
}

void statusMenu(){
	printf("\n*** Cap nhat trang thai ***\n");
	printf("1. Con su dung\n");
	printf("2. Het han\n");
	printf("Thoat\n");
}

void transactionMenu(){
    printf("\n********* TRANSACTION *********\n");
    printf("1. Giao dich nhap/xuat\n");
    printf("2. Lich su giao dich\n");
    printf("3. Thoat\n");
    printf("*******************************\n");
}

void transHistoryMenu(){
	printf("1. Hien thi tat ca lich su giao dich\n");
    printf("2. Tim kiem lich su theo ID\n");
    printf("3. Quay lai\n");
}

void createNewMaterial(struct Product *product){
    int n, i, idx;
	n=themSanPham(0,36-size);
	if(n>36-size){
		printf("\nDanh sach da day\nThem moi that bai\n");
		return;
	}
	for(i=0;i<n;i++){
		idx = size;
	    printf("\nSan pham %d\n", idx + 1);
	
		while(1){
		    printf("Product ID: ");
		    fgets(product[idx].productId, sizeof(product[idx].productId), stdin);
		    product[idx].productId[strcspn(product[idx].productId,"\n")] = '\0';
		    trimSpace(product[idx].productId);
		    if(strlen(product[idx].productId) == 0){
		        printf("ID khong duoc rong\n");
		    }else if(isDuplicateID(product, product[idx].productId)){
		        printf("ID da ton tai\n");
		    }else{
		    	break;
			} 
		}
	
		while(1){
		    printf("Product Name: ");
		    fgets(product[idx].name, sizeof(product[idx].name), stdin);
		    product[idx].name[strcspn(product[idx].name,"\n")] = '\0';
		    trimSpace(product[idx].name);
		
		    if(strlen(product[idx].name) == 0){
		        printf("Ten khong duoc rong\n");
		    }else{
		    	break;
			}
		}
		while(1){
		    printf("Don vi: ");
		    fgets(product[idx].unit, sizeof(product[idx].unit), stdin);
		    product[idx].unit[strcspn(product[idx].unit,"\n")] = '\0';
		    trimSpace(product[idx].unit);
		    if(strlen(product[idx].unit) == 0){
		        printf("Don vi khong duoc rong\n");
		    }else{
		    	break;
			}
		}
	    while(1){
	    	product[idx].qty=nhapSoluong(0);
	    	break;
		}
		product[idx].status = 1;
		size++;
	}
	printf("Them moi thanh cong");
}


void updateProduct(struct Product product[]){
	char id[10];
	int i,found=-1;
	while(1){
		printf("Nhap ma san pham can sua: ");
	    fgets(id,sizeof(id),stdin);
	    id[strcspn(id,"\n")] = '\0';
		trimSpace(id);
		if(strlen(id)==0){
	        printf("ID khong duoc rong\n");
	    }else{
	    	break;
		}
	}
    for(i=0;i<size;i++){
        if(strcmp(product[i].productId, id)==0){
            found = i;
            break;
        }
    }

    if(found == -1){
        printf("Khong tim thay san pham\n");
        return;
    }

    printf("*** Cap nhat thong tin ***\n");
    
    while(1){
        printf("Ten moi: ");
        fgets(product[found].name, sizeof(product[found].name), stdin);
	    product[found].name[strcspn(product[found].name,"\n")] = '\0';
		trimSpace(product[found].name);
	    if(strlen(product[found].name) == 0){
	        printf("Ten khong duoc rong\n");
	    }else{
			break;
		}
	}
	while(1){
        printf("Don vi: ");
        fgets(product[found].unit, sizeof(product[found].unit), stdin);
	    product[found].unit[strcspn(product[found].unit,"\n")] = '\0';
		trimSpace(product[found].unit);
	    if(strlen(product[found].unit) == 0){
	        printf("Ten khong duoc rong\n");
	    }else{
		    break;
		}
	}
    while(1){
	    product[found].qty=nhapSoluong(0);
		break;
	}
    printf("Cap nhat thanh cong\n");
}

void updateStatus(struct Product product[]){
    char id[10];
    int found = -1;
    int i, c;
    while(1){
		printf("Nhap ma san pham can sua: ");
	    fgets(id,sizeof(id),stdin);
	    id[strcspn(id,"\n")] = '\0';
		trimSpace(id);
		if(strlen(id)==0){
	        printf("ID khong duoc rong\n");
	    }else{
	    	break;
		}
	}
    for(i=0;i<size;i++){
        if(strcmp(product[i].productId, id)==0){
            found = i;
            break;
        }
    }

    if(found == -1){
        printf("Khong tim thay ma san pham\n");
        return;
    }
    statusMenu();
    c=luaChon(1,3);
    switch(c){
    	case 1:
    		product[i].status=1;
    		printf("Cap nhat thanh cong");
    		return;
    	case 2:
    		product[i].status=0;
    		printf("Cap nhat thanh cong");
    		return;
    	case 3:
    		return;
	}
}

void searchProduct(struct Product product[]){
    char key[50], keyLower[50];
    char idL[10], nameL[50];
    int found=0;
    int i;
    
    printf("Nhap tu khoa (ID hoac Ten): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key,"\n")] = '\0';
    strcpy(keyLower, key);
    toLowerStr(keyLower);
    
	printf("\n****************************************************************************\n");
    for(i=0;i<size;i++){
        strcpy(idL, product[i].productId);
        strcpy(nameL, product[i].name);
        toLowerStr(idL);
        toLowerStr(nameL);

        if (strstr(idL,keyLower)||strstr(nameL, keyLower)){
            found = 1; 
            printf("Ma san pham: %s|Ten: %s|Don vi: %s|So luong %d|Trang thai: ",product[i].productId,product[i].name,product[i].unit,product[i].qty);
            if(product[i].status==1){
            	printf("Con su dung\n");
			}else{
				printf("Het han\n");
			}
        }
    }

    if(!found){
    	printf("San pham khong ton tai\n");
	}
	printf("****************************************************************************\n");
}

void listProductPaging(struct Product product[]){
    int perPage = 3;
    int page = 1;
    int total,start,end,i,choice,searchChoice;
    if(size == 0){
        printf("Danh sach trong\n");
        return;
    }
    while(1){
        total = (size + perPage - 1) / perPage;
        if (total ==0) total = 1;
        
        start=(page-1)*perPage;
        end=start+perPage;
        if(end>size)end=size;

        printf("\n************************** DANH SACH (Trang %d/%d) **************************\n",page,total);

        for(i=start;i<end;i++){
            printf("Ma san pham: %s  |Ten: %s  |Don vi: %s  |So luong %d  |Trang thai: ",product[i].productId,product[i].name,product[i].unit,product[i].qty);
            if(product[i].status==1){
               	printf("Con su dung\n");
			}else{
				printf("Het han\n");
			}
        }
		printf("****************************************************************************\n");
        printf("\n1.Truoc|2. Sau|3. Chon trang|4.Thoat\n");
        choice=luaChon(1,4);
        if(choice==1&&page>1){
			page--;
		}else if(choice==1&&page==1){
        	printf("Dang o trang dau\n");
		}else if(choice==2 && page<total){
			page++;
		}else if(choice==2 && page==total){ 
			printf("Dang o trang cuoi\n");
		}else if(choice==3){
			printf("Nhap trang can den: ");
    		page=luaChon(1, total);		
		}else if(choice==4){
        	break;
		} 
    }
}

void sortProduct(struct Product product[]){
    int c, i, j, swap;
    struct Product t;

    if(size == 0){
        printf("Danh sach rong\n");
        return;
    }
    do{
        printf("\n1. ID (tang dan)\n2. Ten (A-Z)\n3. Thoat\n");
        c = luaChon(1,3);

        if(c==3) return;

        for(i=0;i<size-1;i++){
            for(j=0;j<size-i-1;j++){
                swap = 0;
                if(c==1 && strcmp(product[j].productId,product[j+1].productId)>0){
					swap = 1;
				}
                if(c==2 && strcmp(product[j].name,product[j+1].name)>0){
                	swap = 1;
				}
                if(swap){
                    t = product[j];
                    product[j] = product[j+1];
                    product[j+1] = t;
                }
            }
        }
        printf("Sap xep thanh cong\n");
        return;
    }while(1);
}

void processTransaction(struct Product product[], struct Transaction transaction[]) {
    char id[10];
    int found = -1;
    int i, type, qty;

    if(size == 0) {
        printf("Danh sach san pham trong.\nVui long them san pham truoc\n");
        return;
    }

	while(1){
		printf("Nhap ID san pham: ");
	    fgets(id,sizeof(id),stdin);
	    id[strcspn(id,"\n")] = '\0';
		trimSpace(id);
		if(strlen(id)==0){
	        printf("ID khong duoc rong\n");
	    }else{
	    	break;
		}
	}
    for(i=0;i<size;i++){
        if(strcmp(product[i].productId, id)==0){
            found = i;
            break;
        }
    }

    if(found == -1){
        printf("San pham khong ton tai\n");
        return;
    }

    printf("Loai giao dich (1. Nhap hang | 2. Xuat hang)\n");
    type = luaChon(1, 2);

    
    qty=nhapSoluong(0);


    if (type == 1) {
        product[found].qty += qty;
        strcpy(transaction[transCount].type, "NHAP");
        printf("Da nhap them %d %s. Tong ton kho: %d\n", qty, product[found].unit, product[found].qty);
    } 
    else if (type == 2) {
        if (product[found].qty < qty) {
            printf("Loi: Ton kho khong du (Hien co: %d)\n", product[found].qty);
            return;
        }
        product[found].qty -= qty;
        strcpy(transaction[transCount].type, "XUAT");
        printf("Da xuat %d %s. Ton kho con lai: %d\n", qty, product[found].unit, product[found].qty);
    } 

    strcpy(transaction[transCount].productId, id);
    transaction[transCount].qty = qty;
    getCurrentDate(transaction[transCount].date); 
    transCount++;
}

void viewTransactionHistory(struct Transaction transaction[], struct Product product[]){
    int perPage = 3;
    int page = 1;
    int total,start,end,i,choice,searchChoice;
    char id[10];
	int found = 0;
    
		
    if(transCount == 0){
        printf("Chua co giao dich nao\n");
        return;
    }
    transHistoryMenu();
    choice=luaChon(1,3);
    switch(choice){
    	case 1:
		    while(1){
		    	total = (transCount + perPage - 1)/perPage;
				if (total ==0){
					total = 1;	
				}
				start=(page-1)*perPage;
				end=start+perPage;
				if(end>transCount){	
					end=transCount;
				}
		    	printf("\n*********************** LICH SU GIAO DICH(Trang %d/%d) ***********************\n",page,total);
		        for(i=start;i<end;i++){
		        	printf("Ma san pham: %s |Loai: %s  |So Luong: %d  |Ngay %s\n",transaction[i].productId, transaction[i].type, transaction[i].qty, transaction[i].date);
		    	}
				printf("****************************************************************************\n");
		        printf("\n1.Truoc|2. Sau|3. Chon trang|4.Thoat\n");
		        choice=luaChon(1,4);
		        if(choice==1&&page>1){
					page--;
				}else if(choice==1&&page==1){
		        	printf("Dang o trang dau\n");
				}else if(choice==2 && page<total){
					page++;
				}else if(choice==2 && page==total){ 
					printf("Dang o trang cuoi\n");
				}else if(choice==3){
					printf("\nNhap trang can tim\n",total);
					searchChoice=luaChon(1,total);
					if(searchChoice >= 1 && searchChoice <= total){
		                page = searchChoice;
						}
				}else if(choice==4){
		        	break;
				} 
		    }
		    break;
		case 2:
        	while(1){
				printf("Nhap ma san pham can tim: ");
				fgets(id,sizeof(id),stdin);
			    id[strcspn(id,"\n")] = '\0';
				trimSpace(id);
				if(strlen(id)==0){
					printf("ID khong duoc rong\n");
				}else{
					break;
				}
			}
			for(i=0;i<size;i++){
			    if(strcmp(product[i].productId, id)==0){
			        found = i;
			        break;
			    }
			}
			if(found == -1){
			    printf("Khong tim thay san pham\n");
			    return;
			}
			while(1){
				printf("\n*************************** LICH SU GIAO DICH **************************\n");
			for(int i=0;i<transCount;i++){
				if(strcmp(transaction[i].productId, id) == 0){
            		found++;
            		printf("Ma san pham: %s |Loai: %s  |So Luong: %d  |Ngay %s\n",transaction[i].productId, transaction[i].type, transaction[i].qty, transaction[i].date);
            	}
			}
			printf("****************************************************************************\n");
			printf("Tong giao dich: %d\n",found);
			break;
			}
			break;
		case 3:
			return;
	}
}

int main(){
    struct Product product[36]={
    	{"1","Ban","Cai",41,1},
    	{"5","Than","Cai",14,1},
    	{"2","Tai","Cai",61,1},
    	{"A","Nuoc","Chai",10,1},
    	{"h","Snack","Goi",50,1},
    	{"D","Keo","Goi",32,1},
	};
    struct Transaction transaction[200]={
    	{"1","NHAP",41,"25/11/2025"},
    	{"5","NHAP",14,"25/11/2025"},
    	{"2","NHAP",61,"25/11/2025"},
    	{"A","NHAP",10,"25/11/2025"},
    	{"h","NHAP",50,"25/11/2025"},
    	{"D","NHAP",32,"25/11/2025"},
	};
    int mainChoice,subChoice;
	
	
    do{
        mainMenu();
        mainChoice=luaChon(1,3);
        switch(mainChoice){
            case 1:
                do{
                    productMenu();
                    subChoice=luaChon(1,7);
                    switch(subChoice){
                        case 1:
							createNewMaterial(product);
							break;
                        case 2:
							updateProduct(product);	
							break;
                        case 3:
							updateStatus(product);	
							break;
                        case 4:
							searchProduct(product);
							break;
                        case 5:
							listProductPaging(product);
							break;
                        case 6:
							sortProduct(product); 
							break;
                        case 7: 
							break;
                    }
                } while(subChoice!=7);
                break;
            case 2:
                do{
                    transactionMenu();
                    subChoice = luaChon(1,3);
                    switch(subChoice){
                        case 1: 
							processTransaction(product, transaction);
							break;
                        case 2: 
							viewTransactionHistory(transaction,product);
							break;
                        case 3:
							break;
                    }
                }while(subChoice!=3);
                break;
            case 3:
            	for(int a=3;a>0;a--){
            		sleep(1);
            		printf("%d\n",a);
				}
                printf("Thoat chuong trinh\n");
                break;
        }
    }while(mainChoice!=3);
    return 0;
}
