#include<errno.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"uici/restart.c"
#include"uici/uici.c"
#include <sys/stat.h>
#include "trt.c"
#include "combine.c"

int main(int argc, char *argv[]) {
	
	if(argc != 2) {
		printf("Invalid number of arguments!!\n");
		return 1;
	}
	
	pid_t downloadTask;
	
	if((downloadTask = fork()) == -1) {
		printf("Failed to fork serverTask!\n");
		return 1;
	}
	
	if(downloadTask == 0) {
		
		while(1) {
		
			FILE *fpt;
			
			char torrentFile[100];
			
			
			printf("[shareX] ");
			// printf("[shareX] ");
			scanf("%s", torrentFile);
			// printf("[shareX] ");
			
			fpt = fopen(torrentFile, "r");
			if(!fpt) {
				printf("No such file exists, Enter a valid name!!\n");
				continue;
			}
			// printf("%s", torrentFile);
			
			fclose(fpt);
			
			int numClients = 2;
			char clientNames[numClients][50];
			u_port_t clientPorts[numClients];
			int checkAvail[numClients];
			int numAvail = 0, i, j = 0, k = 0;
		
			char IPsavailabilityClients[numClients][50];
			int PortsavailabilityClients[numClients];
		
			char hostIP[50];		// Edit
		
			strcpy(clientNames[0], "127.0.0.1");
			clientPorts[0] = 12345;
			
			strcpy(clientNames[1], "127.0.0.1");
			clientPorts[1] = 12346;
		
			// strcpy(clientNames[1], "127.0.0.1");
			// clientPorts[1] = 12346;
		
			int bytescopied;
			int communfd;
			u_port_t portnumber;
		
			/******** Torrent File Information ********/
			
			fpt = fopen(torrentFile, "r");
			
			char fileName[100], name[50];
			int numFragments;
			fscanf(fpt, "%s", fileName);
			strcpy(name, torrentFile);
			fscanf(fpt, "%d", &numFragments);
			int fragmentSize[numFragments];
			for(i = 0; i < numFragments; i++) {
				fscanf(fpt, "%d", &fragmentSize[i]);
			}
			
			fclose(fpt);
		
			////////////////////////////////////////////
		
			for(i = 0; i < numClients; i++) {
	
				portnumber = clientPorts[i];
				strcpy(hostIP, clientNames[i]);
			
				if((communfd = u_connect(portnumber, hostIP)) == -1) {
					printf("Failed to make connection!! test\n");
					return 1;
				}
	
				//printf("[%ld]: Connected %s\n", (long)getpid(), hostIP);
				//bytescopied = copyfile(STDIN_FILENO, communfd);
		
				int query = 1, result;
		
				r_write(communfd, &query, sizeof(int));
		
				query = sizeof(fileName);
		
				r_write(communfd, &query, sizeof(int));
				r_write(communfd, fileName, sizeof(fileName));
		
				r_read(communfd, &result, sizeof(int));
		
				if(result == 1) {
					checkAvail[i] = 1;
					strcpy(IPsavailabilityClients[j], clientNames[i]);
					PortsavailabilityClients[j] = clientPorts[i];
					numAvail++;
					j++;
				} else {
					checkAvail[i] = 0;
					continue;
				}
		
			}
		
			// printf("Total Files Available: %d\n", numAvail);
		
			if(numAvail == 0) {
				printf("This file is unavailable, Look for some other source!!\n");
				continue;
			}
		
			j = 0;
		
			pid_t fragmentDownloading;
		
			struct stat st = {0};

			if (stat("downloaded", &st) == -1) {
	   			mkdir("downloaded", 0700);
			}
		
			struct stat st2 = {0};
		
			char temp[50], temp2[50], temp3[50], name4[100], temp4[50];
			strcpy(temp, "downloaded/");
		
			strcpy(temp2, strcat(temp, fileName));
		
			if (stat(temp2, &st2) == -1) {
	   			mkdir(temp2, 0700);
			}
			
			strcpy(temp4, "/");
			strcpy(name4, strcat(temp2, temp4));
		
			int completedDown = 0;
			
			static char commonPart[100];
			strcpy(commonPart, temp2);
			// int *completedDownPtr = &completedDown;
			char fullFragFileN[numFragments][100];
			
			for(i = 0; i < numFragments; i++) {
				strcpy(temp2, commonPart);
				snprintf(temp, 50, "%d", i);
				strcpy(temp3, strcat(temp2, temp));
				strcpy(fullFragFileN[i], temp3);
			}
		
			for(i = 0; i < numFragments; i++) {
			
				portnumber = PortsavailabilityClients[j];
				strcpy(hostIP, IPsavailabilityClients[j]);
			
				fragmentDownloading = fork();
			
				if(fragmentDownloading == 0) {
					k = 0;
					while(1) {
				
						if((communfd = u_connect(portnumber, hostIP)) == -1) {
							printf("Failed to make connection!!\n");
							return 1;
						}
						
						int query = 3;
						r_write(communfd, &query, sizeof(int));
						
						query = sizeof(fileName);
						
						r_write(communfd, &query, sizeof(int));
						r_write(communfd, fileName, sizeof(fileName));
						
						//printf("[%ld]: Connected %s\n", (long)getpid(), hostIP);
						
						if((communfd = u_connect(portnumber, hostIP)) == -1) {
							printf("Failed to make connection!!\n");
							return 1;
						}					
								
						query = 2;
						r_write(communfd, &query, sizeof(int));
						
						char extFileName[250];
						
						char extFile1[50];
						char extFile2[50];
						char extFile3[50];
						char extFile4[50];
						char extFile5[50];
						char extFile6[50];
						
						strcpy(extFile1, "Temp/");
						strcpy(extFile2, fileName);
						strcpy(extFile3, "/");
						snprintf(extFile4, 50, "%d", i);
						strcpy(extFile5, strcat(extFile1, extFile2));
						strcpy(extFile6, strcat(extFile3, extFile4));
						strcpy(extFileName, strcat(extFile5, extFile6));
						
						query = sizeof(extFileName);
		
						r_write(communfd, &query, sizeof(int));
						r_write(communfd, extFileName, sizeof(extFileName));
			
						size_t sizeFile;
	
						r_read(communfd, &sizeFile, sizeof(size_t));
	
						int file_buffer[sizeFile + 1];
	
						bytescopied = r_read(communfd, file_buffer, sizeFile + 1);
					
						// printf("%s\n", fullFragFileN[i]);
				
						FILE *fp;
						fp = fopen(fullFragFileN[i], "wb");
						if(!fp) {
							continue;
						}
				
						if(fwrite(file_buffer, 1, sizeFile, fp)<0) {
							printf("error writting file\n");
							exit(1);
						}
		
						fclose(fp);
					
						// printf("FileSize: %d\n", (int)bytescopied);
						k++;
				
						if(bytescopied == fragmentSize[i]) {							
							printf("Downloaded Fragment: %d from %d\n", i + 1, j);
							return 0;
						}
				
					
					}
				
				}
				
				// printf("test!!\n");
				// completedDown++;
				// sleep(2);
				
				if(fragmentDownloading == -1) {
					j--;
				}
				
				j++;		
				if(j == numAvail) {
					j = 0;
				}
				
				while(r_waitpid(-1, NULL, WNOHANG) > 0) {}
			
			}
			
			
			int Dflag[numFragments];
			
			for(i = 0; i < numFragments; i++) {
				Dflag[i] = 0;
			}
			
			// printf("%s\n", fullFragFileN[0]);
			
			
			while(completedDown != numFragments) {
				for(i = 0; i < numFragments; i++) {
					// printf("%d", i);
					// printf("number is: %d\n", completedDown);
					FILE *fp = fopen(fullFragFileN[i], "rb");
					if(fp && !Dflag[i]) {
						completedDown++;
						Dflag[i]++;
					}
				}
			}
			
			if(completedDown == numFragments) {
				
				char finalResultPath[100], finalDeletePath[100], finalDeleteComm[150];
				char againTemp2[] = "downloaded/download_";
				char againTemp3[] = "downloaded/";
				char againTemp4[] = "rm -r ";
				strcpy(finalResultPath, strcat(againTemp2, fileName));
				printf("%s\n", finalResultPath);
				combine_file(finalResultPath, numFragments, commonPart);
				
				strcpy(finalDeletePath, strcat(againTemp3, fileName));
				strcpy(finalDeleteComm, strcat(againTemp4, finalDeletePath));
				system(finalDeleteComm);
				
				for(i = 0; i < numAvail; i++) {
				
					portnumber = PortsavailabilityClients[i];
					strcpy(hostIP, IPsavailabilityClients[i]);
					
					if((communfd = u_connect(portnumber, hostIP)) == -1) {
						printf("Failed to make connection!!\n");
						return 1;
					}
				
					int query = 4;
					r_write(communfd, &query, sizeof(int));
				
					query = sizeof(fileName);
						
					r_write(communfd, &query, sizeof(int));
					r_write(communfd, fileName, sizeof(fileName));
				
				}
				
				printf("Download Complete!\n");
			}
			
			// printf("Files Downloaded: %d\n", completedDown);
		
		}
		
		return 0;


	
	} else {
	
		int bytescopied;
		pid_t child;
		char client[MAX_CANON];
		int communfd;
		int listenfd;
		u_port_t portnumber;
	
		portnumber = (u_port_t)atoi(argv[1]);
	
		if((listenfd = u_open(portnumber)) == -1) {
			printf("Failed to create listening endpoint!!\n");
			return 1;
		}
	
		//printf("[%ld]: Waiting for connection on port %d\n", (long)getpid(), (int)portnumber);
	
		while(1) {
			if((communfd = u_accept(listenfd, client, MAX_CANON)) == -1) {
				//printf("Failed to fork a child!\n");
				continue;
			}
		
			//printf("[%ld]: Connected to %s\n", (long)getpid(), client);
			if((child = fork()) == -1) {
				//printf("Failed to fork a child!\n");
				continue;
			}
		
			if(child == 0) {
				// Write Child Code!!
				
				int checkorsend;
				
				r_read(communfd, &checkorsend, sizeof(int));
				
				if(checkorsend == 1) {
					int sizeFileName;
					r_read(communfd, &sizeFileName, sizeof(int));
					char fileName[sizeFileName];
					r_read(communfd, fileName, sizeFileName);
					
					FILE *fp = fopen(fileName, "rb");
					
					if(!fp) {
						int returnRes = 0;
						r_write(communfd, &returnRes, sizeof(int));
					} else {
						int returnRes = 1;
						r_write(communfd, &returnRes, sizeof(int));
					}
					
				}
				
				if(checkorsend == 2) {
					
					sleep(1);
					
					int sizeFileName;
					r_read(communfd, &sizeFileName, sizeof(int));
					char fileName[sizeFileName];
					r_read(communfd, fileName, sizeFileName);
					
					FILE *fp2 = fopen("logs.txt", "a");
					fprintf(fp2, "\n%s\n", fileName);
					fclose(fp2);
					
					while(1) {
					
						FILE *fp;
			  			fp=fopen(fileName, "rb");
			  			if(!fp) {
			    				// printf("File does not exist\n");
			    				continue;
			    			}
			 
			  			fseek(fp,0,SEEK_END);
			  			size_t file_size = ftell(fp);
			  			size_t *ptrSize;
			  			
			  			ptrSize = &file_size;
			  			
			  			r_write(communfd, ptrSize, sizeof(size_t));
			  			
						int file_buffer[file_size + 1];
			  			
			  			fseek(fp,0,SEEK_SET);
			  			if(fread(file_buffer,file_size,1,fp)<=0) {
							printf("unable to copy file into buffer\n");
							exit(1);
			    			}
			    			
			    			r_write(communfd, file_buffer, file_size);
			    			break;
			    			
		    			}
				}
				
				if(checkorsend == 3) {
					
					int sizeFileName;
					r_read(communfd, &sizeFileName, sizeof(int));
					char fileName[sizeFileName];
					r_read(communfd, fileName, sizeFileName);
					
					struct stat st = {0};

					if (stat("Temp", &st) == -1) {
	   					mkdir("Temp", 0700);
					}
		
					struct stat st2 = {0};
		
					char temp[50], temp2[50], temp3[50], temp4[50];
					strcpy(temp, "Temp/");
					strcpy(temp2, strcat(temp, fileName));
					strcpy(temp3, "/");
					strcpy(temp4, strcat(temp2, temp3));
					FILE *fp = fopen("logs.txt", "a");
					// fprintf(fp, "%s", temp4);
					fclose(fp);
		
					if (stat(temp2, &st2) == -1) {
	   					mkdir(temp2, 0700);
					} else {
						return 0;
					}
					
					trt(fileName, temp4);
					
				}
				
				if(checkorsend == 4) {
					
					int sizeFileName;
					r_read(communfd, &sizeFileName, sizeof(int));
					char fileName[sizeFileName];
					r_read(communfd, fileName, sizeFileName);
					
					char againTemp[] = "Temp/";
					char finalDel[150], finalDelCmd[200];
					char againTemp4[] = "rm -r "; 
					strcpy(finalDel, strcat(againTemp, fileName));
					strcpy(finalDelCmd, strcat(againTemp4, finalDel));
					
					system(finalDelCmd);
					
				}
				
				// printf("%d\n", bytescopied);
				if(r_close(listenfd) == -1) {
					//printf("[%ld]: Failed to close listenfd %s\n", (long)getpid(), strerror(errno));
					return 1;
				}
			
				// bytescopied = copyfile(communfd, STDOUT_FILENO);
				//printf("[%ld]: recieved %d bytes!\n", (long)getpid(), bytescopied);
				return 0;
			}
		
			if(r_close(communfd) == -1) {
				printf("[%ld]: Failed to close communfd\n", (long)getpid());
			}
		
			while(r_waitpid(-1, NULL, WNOHANG) > 0) {
		
			}
		
		}
	
	}
	
}

