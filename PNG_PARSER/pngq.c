#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MOST OF THE COMMENTS WERE MADE FOR ME DURING THE EXECUTION IN ORDER NOT TO LOOSE MYSELF AND TO HAVE EVERYTHING CLEAR FOR THE LAYOUTS OF THE CHUNKS AND ALL OTHER THINGS, 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//information taken from documentations that are useful to understand structure of PNG files in order to compute our program :

// The first eight bytes of a PNG file are called magic number or signature

// This signature indicates that the remainder of the file contains a single PNG image, consisting of a series of chunks beginning with an IHDR chunk and ending with an IEND chunk.

// Chunk layout :
// Each chunk consists of four parts:

// Length -> A 4-byte unsigned integer giving the number of bytes in the chunk's data field. The length counts only the data field, not itself, the chunk type code, or the CRC. Zero is a valid length. Although encoders and decoders should treat the length as unsigned, its value must not exceed 231 bytes.
// Chunk Type -> A 4-byte chunk type code. For convenience in description and in examining PNG files, type codes are restricted to consist of uppercase and lowercase ASCII letters (A-Z and a-z, or 65-90 and 97-122 decimal). However, encoders and decoders must treat the codes as fixed binary values, not character strings. For example, it would not be correct to represent the type code IDAT by the EBCDIC equivalents of those letters. Additional naming conventions for chunk types are discussed in the next section.
// Chunk Data -> The data bytes appropriate to the chunk type, if any. This field can be of zero length.
// CRC -> A 4-byte CRC (Cyclic Redundancy Check) calculated on the preceding bytes in the chunk, including the chunk type code and chunk data fields, but not including the length field. The CRC is always present, even for chunks containing no data. See CRC algorithm.
// The chunk data length can be any number of bytes up to the maximum; therefore, implementors cannot assume that chunks are aligned on any boundaries larger than bytes.

// Chunks can appear in any order, subject to the restrictions placed on each chunk type. (One notable restriction is that IHDR must appear first and IEND must appear last; thus the IEND chunk serves as an end-of-file marker.) Multiple chunks of the same type can appear, but only if specifically permitted for that type.

//here I am storing all the possible information that every key of the pformat format asks
struct pformat {
    uint32_t width;
    uint32_t height;
    unsigned char depth;
    char * color_type;
    unsigned int chunk_count;
};

//linked list for the the chunks
struct chunk_layout { 
    unsigned int pos;
    unsigned char * type; 
    uint32_t length; 
    uint32_t CRC;
    unsigned char * data; 
    struct chunk_layout * next;
};

 
struct File {
    const char * f;
    struct pformat * p;
    struct chunk_layout * c;
};


//this is the CRC algorithm taken from w3c documentation as professor suggested :

// THis is the table of CRCs of all 8-bit messages.
unsigned long crc_table[256];

// we will use this variable as a Flag: has the table been computed? Initially false
int crc_table_computed = 0;

//we make the table for a fast CRC
void make_crc_table(void) {
    unsigned long c;
    int n, k;

    for (n = 0; n < 256; n++) {
        c = (unsigned long) n;
        for (k = 0; k < 8; k++) {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[n] = c;
    }
    crc_table_computed = 1;
};

/* Update a running CRC with the bytes buf[0..len-1]--the CRC
    should be initialized to all 1's, and the transmitted value
    is the 1's complement of the final running CRC (see the
    crc() routine below)). */

unsigned long update_crc(unsigned long crc, unsigned char *buf, int len) {
    unsigned long c = crc;
    int n;
    if (!crc_table_computed)
        make_crc_table();
    for (n = 0; n < len; n++) {
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}


// printusage function gets called when we we pass no command line arguments 
void printUsage() {
    printf("Usage: ./pngq [options] file1 [options] file2 file3...\n");
}


//function used to free all the allocated memory
void deleteAllocated(struct File * toFree) {
    /*we need to free memory that we allocated*/
    if(toFree->p) {
        free(toFree->p);
    }
    if (toFree->c) {
        while(toFree->c) {
            struct chunk_layout * itr = toFree->c->next;
            if (toFree->c->data != 0) {
                free(toFree->c->data);
            }
            free(toFree->c->type);
            free(toFree->c);
            toFree->c = itr;
        }
    }
    free(toFree);
    return;
}


void printTheFile(struct File * ftoprint, const char *pformat, const char *cf, const char *kf) {
    //we need to iterate over the formats string which means
    while(*pformat != 0) {
        /*iterate over the string*/
        if(*pformat == '_') {
            if(++pformat) {
                switch(*pformat) {
                    case 'f' :
                        printf("%s", ftoprint->f);
                        ++pformat;
                        break;
                    case 'w' :
                        printf("%u", ftoprint->p->width);
                        ++pformat;
                        break;
                    case 'h' :
                        printf("%u", ftoprint->p->height);
                        ++pformat;
                        break;
                    case 'c' :
                        printf("%s", ftoprint->p->color_type);
                        ++pformat;
                        break;
                    case 'd' :
                        printf("%u", ftoprint->p->depth);
                        ++pformat;
                        break;
                    case 'N' :
                        printf("%u", ftoprint->p->chunk_count);
                        ++pformat;
                        break;
                    case 'C' :
                        struct chunk_layout * itr = ftoprint->c;
                        unsigned int j = 0;
                        while(itr) {
                            while(cf[j] != 0) {  
                                if(cf[j] == '_') {
                                    ++j;
                                    if (cf[j] == 0)
                                        break;
                                    switch(cf[j]) {
                                        case 'n' :
                                            printf("%u", itr->pos);
                                            ++j;
                                            break;
                                        case 't' :
                                            printf("%c%c%c%c", itr->type[0],itr->type[1],itr->type[2],itr->type[3]);
                                            ++j;
                                            break;
                                        case 'l' :
                                            printf("%u", itr->length);
                                            ++j;
                                            break;
                                        case 'D' :
                                            unsigned counter = 0;
                                            for(unsigned int i=0; i < itr->length; ++i) {
                                                ++counter;
                                                if(counter < 16) {
                                                    printf(" %2x", itr->data[i]);
                                                } else {
                                                    counter = 0;
                                                    printf("\n");
                                                    printf(" %2x", itr->data[i]);
                                                }    
                                            } 
                                            ++j;
                                            break;
                                    }                          
                                } else {
                                     if(cf) {
                                        printf("%c", cf[j]);
                                        ++j;
                                    }
                                }
                            }
                            itr = itr->next;
                            j = 0;
                        }
                        ++pformat;
                        break;
                    case 'K' :
                        struct chunk_layout * p = ftoprint->c;
                        unsigned int k = 0;
                        unsigned counter =0;
                        while(p) {
                            if ((memcmp(p->type, "tEXt",4) == 0)) {
                                while(kf[k] != 0) {  
                                    if(kf[k] == '_') {
                                        ++k;
                                        if (kf[k] == 0)
                                            break;
                                        switch(kf[k]) { 
                                            case 'k':
                                                unsigned int i = 0;
                                                while(p->data[i] != 0) {
                                                    ++counter;
                                                    printf("%c",p->data[i]);
                                                    ++i;
                                                }
                                                ++k;
                                                break;
                                            case 't':
                                                unsigned char * iter = p->data + counter;
                                                while(*iter != 0) {
                                                    printf("%c", *iter);
                                                    ++iter;
                                                }
                                                ++k;
                                                break;
                                        }
                                    } else {
                                        if(kf) {
                                            printf("%c", cf[k]);
                                            ++k;
                                        }
                                    }
                                }
                            }
                            p = p->next;
                            k=0;
                        }
                        ++pformat;
                        break; 
                }
            }
        } else {
            if(pformat) {
                printf("%c", *pformat);
                ++pformat;
            }
        }
    }
    deleteAllocated(ftoprint);
    return;
};


// //processFile function is the core function which will process all the PNG's that we pass on the command line  
int processFile(const char *filename, const char *pformat, const char *chunk_layout, const char *kformat) {

    //we open the file in binary read mode  
    FILE * file = fopen(filename, "rb");

    //if something goes wrong with the opening of the file we print a specific error message 
    if (!file) {
        fprintf(stderr, "it was not possible to open file %s, an error popped up\n", filename);
        return -1;
    }

    //we initialize the file structure here that we will fill later with the loop 
    struct File * iteratedFile = malloc(sizeof(struct File));

    if (!iteratedFile) {
        fprintf(stderr, "Memory allocation failed\n");
        goto errors;
    }
    iteratedFile->f = filename;
    iteratedFile->p = 0; //initiliaze them to null pointer
    iteratedFile->c = 0; //initialize them to null pointer


    //if we are here it means that we open the file correctly and we can start iterating over the file

    // we need to remember that the file initially has the 8 magic numbers which we need to skip because are information that are out of our interest
    // in order to skip this magic numbers we can use the function fseek which reporting from documetation :

                // Sets the file position indicator for the file stream stream to the value pointed to by offset.
                // If the stream is open in binary mode, the new position is exactly offset bytes measured from the beginning of the file if origin is SEEK_SET,

    unsigned char Png[8];           
    if ((fread(Png, 1, 8,  file)) != 8)
        goto errors;

    //check the signature of the png to see if it is valid, we can see from documentation that this is what we need to check so we do it like this
    //to avoid warnings needed to cast do this ugly stuff(I think it's ugly maybe I am wrong)
    if (strlen((char *)Png)) {
        if (Png[1] != 'P' || Png[2] != 'N' || Png[3] != 'G') 
            goto errors;
    }

    // As said, after the signature, the file structure is divided into "chunks" of data. Every chunk has its own structure, in the case of PNG, the chunk structure contains:

                    // Type
                    // Length
                    // Data
                    // CRC

    // There are three chunks that must be present on every valid PNG image. They are called "critical chunks." These are:

                    // IHDR
                    // IDAT
                    // IEND

    //we can have 3 flags to be sure that this are present
    unsigned int IHDR = 0;
    unsigned int IDAT = 0;
    unsigned int IEND = 0;

    // we wanna have a variable that stores the how many chunks the file has 
    unsigned int chunkCounter = 0;

    //now we read need to read the first chunk which ideally should be IHDR 
    //remember that first 4 bytes that tells us the LENGTH 
    //second 4 bytes tells us the CHUNK TYPE
    //then we have the DATA
    //at the end we have the 4 bytes for the CRC
    
    //we use the function fread to help us going through the data, fread reads from the stream up to a count number storing them into a buffer that we pass.
    //the beauty of fread is that The file pointer for the stream is advanced by the number of characters read.
    while (file) {

        unsigned char length[4];
        uint32_t len = 0;
        if ((fread(length, 1, 4, file)) != 4) 
            goto errors;
        for (int i =0; i <4; ++i) {
            len = len*256 + length[i];
        }

        unsigned char chunk_type[4];
        if ((fread(chunk_type, 1, 4, file)) != 4) 
            goto errors;

        //we take care of the flags 
        if (memcmp(chunk_type, "IHDR", 4) == 0 ) {  
            ++chunkCounter; 
            IHDR = 1; //flag to true which means found it tha chunk IHDR 

            //we do things only for the IHDR that is different from the others

            
            //The IHDR chunk must appear FIRST and it contains:

                // Width:              4 bytes
                // Height:             4 bytes
                // Bit depth:          1 byte
                // Color type:         1 byte
                // Compression method: 1 byte
                // Filter method:      1 byte
                // Interlace method:   1 byte

            unsigned char width[4];
            unsigned char height[4];
            unsigned char bit_depth;
            unsigned char color_type;
        
            //width cannot be 0
            uint32_t wid;
            if ((fread(width,1,4,file)) != 4) //read and put in width
                goto errors;
            for(int i =0; i<4; ++i) {
                wid = wid*256 + width[i];
            }
            //check the if result is valid
            if(wid == 0) {
                goto errors;
            }

            //height cannot be 0
            uint32_t hei;
            if ((fread(height,1,4,file)) != 4)
                goto errors; 
            for(int i =0; i<4; ++i) {
                hei = hei*256 + height[i];
            }
            //check the if result is valid
            if(hei == 0) {
                goto errors;
            }

            //bit_depth 1,2,4,8,16 are the valid ones
            if((fread(&bit_depth,1,1,file)) != 1)
                goto errors;
            //check the if result is valid
            if ( ( (bit_depth % 2) != 0 || bit_depth > 16 ) &&  bit_depth != 1) {
                goto errors;
            }

            //valid values are 0,2,3,4,6
                // 0 -> Grayscale 
                // 2 -> Truecolor 
                // 3 -> Indexed-color 
                // 4 -> Grayscale with alpha channel
                // 6 ->  Truecolor with alpha channel
            if((fread(&color_type,1,1,file)) != 1)
                goto errors;
            //check the if result is valid
            if( ((color_type % 2) != 0 || color_type > 6 ) && color_type != 3) {
                goto errors;
            }

            //we start creating the structure for the pformat 
            struct pformat * pp = malloc(sizeof(struct pformat));

            //check if allocation has failed 
            if(!pp) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }
            pp->width = wid; //width we got with fread
            pp->height = hei; // height we got with fread
            pp->depth = bit_depth; //depth we got with fread
            switch (color_type) {  //switch case to to what color the byte we got corresponds
                case 0 :
                    pp->color_type = "Grayscale";
                    break;
                case 2 :
                    pp->color_type = "Truecolor";
                    break;
                case 3 :
                    pp->color_type = "Indexed-color";
                    break;
                case 4 :
                    pp->color_type = "Grayscale with alpha channel";
                    break;
                case 6 :
                    pp-> color_type = "Truecolor with alpha channel";
                    break;   
            }

            //we check that we the IHDR is the first and the ONLY ONE 
            if (chunkCounter != 1) {
                goto errors;
            }
            //we still don't know the actual count but for the moment if we are here we got 1 chunk so we initiliaze it to 1
            pp->chunk_count = chunkCounter; 

            //link the p structure to the file 
            iteratedFile->p = pp;


            //recreate the data by arranging together the pieces we already read and the last that we need to read
            unsigned char data[13];
            memcpy(data, width, 4);
            memcpy(data + 4, height, 4);
            data[8] = bit_depth;
            data[9] = color_type;
            unsigned char methods[3];
            fread(methods, 1,3,file);
            memcpy(data + 10, methods, 3);

            //allocate memory for the data
            unsigned char * dd = malloc(13);
            if (!dd) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }
            memcpy(dd, data, 13);

            //we allocate memory to create the chunk_layout 
            struct chunk_layout * chunk = malloc(sizeof(struct chunk_layout));

            //check if memory allocation failed 
            if (!chunk) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }

            //allocate memory for the type 
            unsigned char * tt_allocated = malloc(4);
            if(!tt_allocated) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }
            memcpy(tt_allocated, chunk_type, 4);

            chunk->pos = chunkCounter;
            chunk->type = tt_allocated; 
            chunk->length = len; 

            //read the crc           
            unsigned char chunk_crc[4];
            uint32_t c_crc;
            if((fread(chunk_crc, 1, 4, file)) != 4)
                goto errors;
            for(unsigned int i =0; i<4; ++i) {
                c_crc = c_crc *256 + chunk_crc[i];
            }

            //compute the crc check
            unsigned long crc = update_crc(0xffffffffUL, chunk_type, 4);
            crc = update_crc(crc, data, 13);
            crc ^= 0xffffffffUL;
            //now we need to see if it is a valid CRC 
            if (crc != c_crc) { 
                goto errors;
            } 
            chunk->CRC = c_crc; 
            chunk->data = dd; 
            chunk->next = 0; //if we are here the next one is obviously a null ptr
            //we link the chunk_layout to the file 
            iteratedFile->c = chunk;


            //once we are here IHDR is finished which means that we can watch the next chunk so we go on with the loop
            continue;
        } 

        if (memcmp(chunk_type, "IDAT",4) == 0) {
            ++chunkCounter;
            IDAT = 1;
        }
       
        if (memcmp(chunk_type, "IEND",4) == 0){
            ++chunkCounter;            
            IEND = 1;
            //The IEND chunk must appear LAST. It marks the end of the PNG datastream. The chunk's data field is empty.
            //the structure of the IEND has no data which means it only has:
                // 4 byte for the length 
                // 4 bytes ofr the chunk types 
                // and the CRC 

            unsigned char chunk_crc[4];
            uint32_t c_crc;
            if((fread(chunk_crc, 1, 4, file)) != 4)
                goto errors;
            for(unsigned int i = 0; i < 4; ++i) {
                c_crc = c_crc*256 + chunk_crc[i];
            }

            unsigned long crc = update_crc(0xffffffffUL, chunk_type, 4);
            crc ^= 0xffffffffUL;
            if (crc != c_crc) { 
                goto errors;
            } 

            struct chunk_layout * new_chunk = malloc(sizeof(struct chunk_layout));

            //check if memory allocation failed 
            if (!new_chunk) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }

            unsigned char tt[4];
            memcpy(tt,chunk_type,4);

            unsigned char * tt_allocated = malloc(4);
            if (!tt_allocated) {
                fprintf(stderr, "Memory allocation failed\n");
                goto errors;
            }
            memcpy(tt_allocated, tt, 4);

            //when we are here there will be already the first or many more chunk_layout in the linked list
            //so we fill our new one that will be attached 
            new_chunk->pos = chunkCounter;
            new_chunk->type = tt_allocated;
            new_chunk->length = len;
            new_chunk->CRC = c_crc;
            new_chunk->data = 0; //there is no data 
            new_chunk->next = 0; //null ptr

            //link the chunk_layout of the new chunk to the linked list 
            struct chunk_layout * itr = iteratedFile->c;
            while (itr->next != 0) {
                itr = itr->next;
            }

            //we arrive here which means we reached the end of the linked list
            itr->next = new_chunk;

            //we have officially iterated over the all file
            break;
        }


        //needed to keep truck of the cunkCount
        if ((memcmp(chunk_type, "IHDR", 4) != 0) && (memcmp(chunk_type, "IDAT",4) != 0) && (memcmp(chunk_type, "IEND",4) != 0)) {
            ++chunkCounter;
        }

        //we allocate memory to store the data for which we already know the length ONLY OF THE DATA
        unsigned char * dataInStruct = malloc(len);
        if(!dataInStruct) {
            fprintf(stderr, "Memory allocation failed\n");
            goto errors;
        }
        //we read the data
        if (fread(dataInStruct, 1,len,file) != len)
            goto errors;

        // once we've read the data we go on with the checksum validation 
        unsigned char chunk_crc[4];
        uint32_t c_crc;
        if((fread(chunk_crc, 1, 4, file)) != 4)
            goto errors;
        for (unsigned int i =0; i < 4; ++i){
            c_crc = c_crc*256 + chunk_crc[i];
        }

        unsigned long crc = update_crc(0xffffffffUL, chunk_type, 4);
        crc = update_crc(crc, dataInStruct, len);
        crc ^= 0xffffffffUL;
        if (crc != c_crc) { 
            goto errors;
        } 

        //if we are here now we need to create the chunk_layout for the actual chunk
        //we allocate memory to create the chunk_layout 
        struct chunk_layout * new_chunk = malloc(sizeof(struct chunk_layout));

        //check if memory allocation failed 
        if (!new_chunk) {
            fprintf(stderr, "Memory allocation failed\n");
            goto errors;
        }

        unsigned char tt[4];
        memcpy(tt,chunk_type,4);

        unsigned char * tt_allocated = malloc(4);
        if (!tt_allocated) {
            fprintf(stderr, "Memory allocation failed\n");
            goto errors;
        }
        memcpy(tt_allocated, tt, 4);

        //when we are here there will be already the first or many more chunk_layout in the linked list
        //so we fill our new one that will be attached 
        new_chunk->pos = chunkCounter;
        new_chunk->type = tt_allocated;
        new_chunk->length = len;
        new_chunk->CRC = c_crc;
        new_chunk->data = dataInStruct;
        new_chunk->next = 0;

        //we iterate over all the chunk_layout linked list 
        struct chunk_layout * itr = iteratedFile->c;
        while (itr->next != 0) {
            itr = itr->next;
        }
        //we arrive here which means we reached the end of the linked list
        //link the chunk_layout of the new chunk to the linked list
        itr->next = new_chunk;

     }

    //if we are here everything went well and we can finish our pformat structure inside of our file structure 
    iteratedFile->p->chunk_count = chunkCounter; 

    //now we fully iterated over the file which means that we need to check the flags that we provided initially and if even 1 is still 0 we go to errors
    if (IHDR == 0 || IDAT == 0 || IEND == 0) {
        goto errors;
    }

    printTheFile(iteratedFile, pformat, chunk_layout, kformat);
    if(file) {
        fclose(file);
    }

    return 1;
    
    errors :
        if(iteratedFile) {
            deleteAllocated(iteratedFile);
        }
        fclose(file);
        return -1;
}



int main(int argc, char *argv[]) {

    
    if (argc < 2) {
        printUsage(); //if you pass no arguments, the program will print a usage message, professor did this in class too
        return 1;
    }


    //we initialize the default values for the formats  
    const char *pformat = "_f: _w x _h, _c, _d bits per sample, _N chunks\n_C";
    const char *cformat = "\t_n: _t (_l)\n";
    const char *kformat = "\t_k: _t\n";

    //this loop we checks the command line arguments to see what formats we should print and we store them into the right formats
    for (int i = 1; i < argc; ++i) {  
        if (strncmp(argv[i], "p=", 2) == 0) {
            pformat = argv[i] + 2; 
        } else if (strncmp(argv[i], "c=", 2) == 0) {
            cformat = argv[i] + 2;
        } else if (strncmp(argv[i], "k=", 2) == 0) {
            kformat = argv[i] + 2;
        } else if (strcmp(argv[i], "--") == 0) {
            //when we find this we will need to scan the command line up until the next format information
            ++i ;
            while (i < argc) {
                //if we are here it means that we are reading all argyments as a file, and for every file we will need to call it with the same format requests 
                processFile(argv[i], pformat, cformat, kformat);
                ++i;
            }
            //
            break;
        } else {
            while( (strncmp(argv[i], "p=", 2) != 0) && (strncmp(argv[i], "c=", 2) != 0) && (strncmp(argv[i], "k=", 2) != 0)  && (strcmp(argv[i], "--") != 0) && i < argc) {
                processFile(argv[i], pformat, cformat, kformat);
                if(++i >= argc) {
                    return 1;
                }
            }
            if(i >= argc) {
                return 1;
            } else {
                --i;
            }
         }
     }
}
