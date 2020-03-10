#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define nmedias 4
#define min 6
#define maxalunos 50
typedef struct{
    int matricula;
    float nota[nmedias];
    float media;
}boletim;
void adquirir(boletim *aluno){
    printf("Digite a matricula do aluno: ");
    scanf("%d",&aluno->matricula);
    int i;
    float s = 0;
    for(i = 0;i < nmedias;i++){
        printf("Digite a nota %d do aluno %d: ",i,aluno->matricula);
        scanf("%f",&aluno->nota[i]);
        s += aluno->nota[i];
    }
    aluno->media = s/nmedias;
    printf("Pronto!\n");
}
void imprimir(boletim *list,int quantidade){
    int i,j;
    printf("Mat\t");
    for(i = 0;i < nmedias;i++){
        printf("N%d\t",i);
    }
    printf("Media\tResultado\n");
    for(i = 0;i < quantidade;i++){
        printf("%d\t",list[i].matricula);
        for(j = 0;j < nmedias;j++){
            printf("%.1f\t",list[i].nota[j]);
        }
        printf("%.3f\t",list[i].media);
        list[i].media >= min?printf("AP\n"):printf("RP\n");
    }
}
int compmedia(const void *m1,const void *m2){
    boletim *a;
    a = m1;
    boletim *b;
    b = m2;
    return (int)(b->media*1000 - a->media*1000);
}
void gravar(void * restrict ptr,int q){
    FILE *arquivo;
    char str[20],str2[50] = "";
    printf("Digite o nome do Arquivo: ");
    fflush(stdin);
    scanf("%s",str);
    strcat(str2,str);
    strcat(str2,".bin");
    arquivo = fopen(str2,"wb");
    fflush(arquivo);
    int size = sizeof(boletim)*q;
    fprintf(arquivo,"%d\n",q);
    fwrite(ptr,size,q,arquivo);
    fclose(arquivo);
}
void ler(void *p,int *qt){
    FILE *arquivo;
    char str[20],str2[45] = "";
    printf("Digite o nome do Arquivo: ");
      fflush(stdin);
    scanf("%s",str);
    strcat(str2,str);
    strcat(str2,".bin");
    arquivo = fopen(str2,"rb");
    !arquivo?ler(p,qt):1;
    fscanf(arquivo,"%d\n",qt);
    int size = sizeof(boletim)*(*qt);
    fread(p,size,(*qt),arquivo);
    fclose(arquivo);
    qsort(p,(*qt),sizeof(boletim),compmedia);
}
void exportar(void * restrict p,int q){
    FILE *arquivo;
    boletim *array = p;
    char str[20],str2[45] = "";
    printf("Digite o nome do Arquivo: ");
    fflush(stdin);
    scanf("%s",str);
    strcat(str2,str);
    strcat(str2,".txt");
    arquivo = fopen(str2,"w");
    int i,j;
    fprintf(arquivo,"Mat\t");
    for(i = 0;i < nmedias;i++){
        fprintf(arquivo,"N%d\t",i);
    }
    fprintf(arquivo,"Media\tResultado\n");
    for(i = 0;i < q;i++){
        fprintf(arquivo,"%d\t",array[i].matricula);
        for(j = 0;j < nmedias;j++){
            fprintf(arquivo,"%.1f\t",array[i].nota[j]);
        }
        fprintf(arquivo,"%.3f\t",array[i].media);
        array[i].media >= min?fprintf(arquivo,"AP\n"):fprintf(arquivo,"RP\n");
    }
    fclose(arquivo);
    printf("Pronto!");
}
int main(){
    int q = 0,i;
    boletim list[maxalunos];
    char choice;
    goto menu;
    /*b:
    printf("1 - Menu\n2 - Entrada\n-");
    char choice;
    scanf(" %c",&choice);
    switch(choice){
        case '1':goto c3;
        case '2':goto c1;
        default :goto b;
    }*/
    acq:
    printf("Qual e o numero de alunos da turma? ");
    scanf("%d",&q);
    for(i = 0;i < q;i++){
        adquirir(&list[i]);
    }
    qsort(list,q,sizeof(boletim),compmedia);
    print:
    imprimir(&list[0],q);
    menu:
    printf("1 - Cadastrar turma\n2 - Adicionar Aluno\n3 - Modificar Info. de um Aluno\n4 - Imprimir Turma\n5 - Salvar\n6 - Carregar\n7 - Exportar\n8 - Finalizar\n-");
    scanf(" %c",&choice);
    switch(choice){
        case '1':goto acq;
        case '2':adquirir(&list[q]);
                 q++;
                 break;
        case '3':
                printf("Digite a matricula do aluno: ");
                int mat,st = 0;
                scanf("%d",&mat);
                for(i = 0;i < q;i++){
                    if(list[i].matricula == mat){
                        adquirir(&list[i]);
                        st = 1;
                        break;
                    }
                }
                st?0:printf("Matricula inexistente!");
                break;
        case '4':goto print;
        case '5':gravar(&list,q);
                 break;
        case '6':ler(&list,&q);
                 break;
        case '7':exportar(&list,q);
                 break;
        case '8':return 105;
        default :goto menu;
    }
    goto menu;
}
