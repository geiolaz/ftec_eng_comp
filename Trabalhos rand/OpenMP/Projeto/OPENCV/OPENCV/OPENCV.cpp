#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <fstream>

using namespace cv;
using namespace std;
using  ms = chrono::milliseconds;
using get_time = chrono::steady_clock;



int TRHEADCOUNT, i;



void testa(int TRHEADCOUNT) {
	//Teste de startup-----------------------------------------------------------------
	int num_thds, myid;
	printf("\n TRHEADCOUNT definido: %d\n\n", TRHEADCOUNT);

	omp_set_num_threads(TRHEADCOUNT);
#pragma omp parallel
	{
		num_thds = omp_get_num_threads(); //threads criados
		myid = omp_get_thread_num(); //Numero de identificação do thread
		printf(" Hello world do thread: %d de %d trheads!\n", (1 + myid), num_thds);
	}
	//Fim do teste de startup----------------------------------------------------------
}




int main()
{
	//startup-----------------------------------------------
	int TRHEADCOUNT = 4; //inicializa com 4 threads, pode ser modificado
	int i;
	printf("Carregando imagens\n");
	Mat img1 = imread("1.jpg", CV_LOAD_IMAGE_COLOR);
	//Mat img2 = imread("2.jpg", CV_LOAD_IMAGE_COLOR);
	printf("Imagens carregadas\n");

	int imput = 0, rodando = 1;
	do {
		printf("\n0-SAIR\t 1-Set numero de threads\t 2-Testar Threads \t 3-Trabalhar \n 4- Exibir imagem \t 5- Limpa tela\n");
		scanf_s("%d", &imput);

		switch (imput) {
		case 5:
			system("cls");
			break;
		case 4:
			namedWindow("aaa",CV_WINDOW_FREERATIO);
			resizeWindow("aaa", 800, 800);
			imshow("aaa", img1);

			break;
		case 0:
			rodando = 0;
			break;
		case 1:
			printf("\nDigite um numero:\n");
			scanf_s("%d", &TRHEADCOUNT);
			break;

		case 2:
			testa(TRHEADCOUNT);
			break;

		case 3:
			//parte importante------------------------------------------------------------
			auto start = get_time::now(); //contagem do tempo
			 //--------------------------------------------------------------------------------- TIMER
#pragma omp parallel for
			for (int r = 0; r < img1.rows; r++) {//percore linha

				for (int c = 0; c < img1.cols; c++) {//percore coluna

					img1.at<cv::Vec3b>(r, c)[0] = img1.at<cv::Vec3b>(r, c)[0] * c;//trabalha azul
				}
			}

#pragma omp parallel for
			for (int r = 0; r < img1.rows; r++) {//percore linha

				for (int c = 0; c < img1.cols; c++) {//percore coluna

					img1.at<cv::Vec3b>(r, c)[1] = img1.at<cv::Vec3b>(r, c)[1] * c;//trabalha amarelo
				}
			}

#pragma omp parallel for
			for (int r = 0; r < img1.rows; r++) {//percore linha

				for (int c = 0; c < img1.cols; c++) {//percore coluna

					img1.at<cv::Vec3b>(r, c)[2] = img1.at<cv::Vec3b>(r, c)[2] * c;//trabalha vermelho
				}
			}


			//--------------------------------------------------------------------------------- TIMER
			auto end = get_time::now();//contagem do tempo
			auto diff = end - start;
			cout << "Tempo passado  de:  " << chrono::duration_cast<ms>(diff).count() << " milissegundos " << endl;
			
			imwrite("output.jpg", img1);
			break;
			

		}



	} while (rodando == 1);//fim laço de menu -----------------------------------------

	printf("Programa finalizado\n");
	system("PAUSE");
	return 0;
}