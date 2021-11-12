#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>
#include<stdbool.h>
#define AGE_RESTRICTION 18
#define LOWER 10000
#define UPPER 99999

struct Appointment
{
    char first_appointment_status;
    char second_appointment_status;
    long long center_id;
    char vaccine_type[12];
};

struct Beneficiary
{
    long long id;
    int year_of_birth;
    int number_of_doses_taken;
    struct Appointment appointment;
    char name[100];
    char gender[10];
};

struct Vaccine
{
    long long covaxin, covishield, sputnik, zydus, Pfizer, moderna;
};

struct Center
{
    long long PIN;
    long long id;
    char address[94];
    struct Vaccine vaccine;
    char district[30];
    char center_type[12];
};

struct Beneficiary* beneficiary;
struct Center* center;
int beneficiary_record_size = 1;
int center_record_size = 1;
struct Vaccine vaccine;

void swap_struct_center(struct Center *a, struct Center *b)
{
    struct Center temp = *a;
    *a = *b;
    *b = temp;
}

void set_default_Bene(struct Beneficiary *B)
{
    B->id = 100000;
    B->year_of_birth = 2020;
    B->number_of_doses_taken = 0;
    B->appointment.first_appointment_status = 'n';
    B->appointment.second_appointment_status = 'n';
}

void set_default_center(struct Center *center)
{
    center->id = LLONG_MAX;
    center->PIN = 0;
    center->vaccine.covaxin = 0;
    center->vaccine.covishield = 0;
    center->vaccine.sputnik = 0;
    center->vaccine.zydus = 0;
    center->vaccine.Pfizer = 0;
    center->vaccine.moderna = 0;
};

void set_default_vaccine(struct Vaccine *vaccine)
{

    vaccine->covaxin = 0;
    vaccine->covishield = 0;
    vaccine->sputnik = 0;
    vaccine->zydus = 0;
    vaccine->Pfizer = 0;
    vaccine->moderna = 0;
};

void addNewBeneficiary(char name[], char gender[], int year_of_birth)
{
    long long random = rand();
    long long generated_id = (random % (UPPER - LOWER + 1)) + LOWER;

    int flag = 0, storing_index = 0, i = 0;
    while(i < beneficiary_record_size) // Checking uniqueness of the generated id
    {
        
        if(generated_id == (*(beneficiary + i)).id)
        {
            generated_id = (random % (UPPER - LOWER + 1)) + LOWER;
            flag = 1;
        }
        
        i++;
        if(flag == 1)
        {
            i = 0;
            flag = 0;
        }

    }
    i = 0;
    flag = 0;
    while(i < beneficiary_record_size && flag == 0) // finding the index at which data should be inserted
    {
        
        if((*(beneficiary + i)).id > generated_id)
        {
            storing_index = i;
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    i = beneficiary_record_size - 1;

    while(i > storing_index) // shifting records to right from sorting position
    {
        (*(beneficiary + i)) = (*(beneficiary + i - 1));
        i--;
    }
    (beneficiary+storing_index)->id = generated_id;
    strcpy((*(beneficiary + storing_index)).name,name);
    strcpy((*(beneficiary + storing_index)).gender,gender);
    (*(beneficiary + storing_index)).year_of_birth = year_of_birth;
    // i = 0;
    // while (i < beneficiary_record_size)
    // {
    //     printf("%lld %s %s %d\n",((beneficiary+i)->id), ((beneficiary+i)->name), ((beneficiary+i)->gender), ((beneficiary+i)->year_of_birth));
    //     i++;
    // }
    // printf("\n");
    beneficiary_record_size += 1;
    beneficiary = realloc(beneficiary, beneficiary_record_size*sizeof(struct Beneficiary));
    set_default_Bene(beneficiary + (beneficiary_record_size -1));
    
}

void addNewCenter(long long center_id, char address[], char district[], long long PIN, char center_type[], struct Vaccine *vaccine)
{
    
    int flag = 0, storing_index = 0, i = 0;
    while(i < center_record_size && flag == 0) // finding the index at which data should be inserted
    {
        
        if((*(center + i)).id > center_id)
        {
            storing_index = i;
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    i = center_record_size - 1;

    while(i > storing_index) // shifting records to right from sorting position
    {
        (*(center + i)) = (*(center + i - 1));
        i--;
    }
    (center + storing_index)->id = center_id;
    strcpy((*(center + storing_index)).address,address);
    strcpy((*(center + storing_index)).district,district);
    strcpy((*(center + storing_index)).center_type,center_type);
    (center + storing_index)->PIN = PIN;
    ((center+storing_index)->vaccine).covaxin = (*vaccine).covaxin;
    ((center+storing_index)->vaccine).covishield = (*vaccine).covishield;
    ((center+storing_index)->vaccine).Pfizer = (*vaccine).Pfizer;
    ((center+storing_index)->vaccine).sputnik = (*vaccine).sputnik;
    ((center+storing_index)->vaccine).zydus = (*vaccine).zydus;
    ((center+storing_index)->vaccine).moderna = (*vaccine).moderna;
    // i = 0;
    // while (i < center_record_size)
    // {
    //     printf("%lld %s %s %lld %s ",(*(center+i)).id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
    //     printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",((center+i)->vaccine).covaxin, ((center+i)->vaccine).covishield, ((center+i)->vaccine).sputnik,((center+i)->vaccine).zydus,((center+i)->vaccine).Pfizer,((center+i)->vaccine).moderna);
    //     i++;
    // }
    // printf("\n");
    center_record_size++;
    center = realloc(center, center_record_size*sizeof(struct Center));
    set_default_center(center + (center_record_size -1));
    
}

void bubbleSort_PIN(struct Center *a)
{
   int i, j;
   int flag = 1;
   for (i = 0; ((i < center_record_size-2) && (flag == 1)); i++)
   {
        flag = 0;
        for (j = 0; j < center_record_size - i - 2; j++)
        {
            
            if ((*(a + j)).PIN > (*(a + j + 1)).PIN)
            {
                swap_struct_center((a + j), (a + j+1));
                flag = 1;
            }
        }
   }
}

void bubbleSort_district(struct Center *a)
{
   int i, j;
   int flag = 1,compare;
   for (i = 0; ((i < beneficiary_record_size-1) && (flag == 1)); i++)
   {
        flag = 0;
        for (j = 0; j < beneficiary_record_size - i - 1; j++)
        {
            compare = strcmp((*(a + j)).district , (*(a + j + 1)).district);
            if (compare > 1)
            {
                swap_struct_center((a + j), (a + j+1));
                flag = 1;
            }
        }
   }
}

void EnlistSortedCenters(char searchBy[])
{
    struct Center *temp;
    temp = (struct Center *)malloc(center_record_size * sizeof(struct Center));
    for(int i = 0; i < center_record_size; i++)
    {
        *(temp + i) = *(center + i);
    }

    int i = 0;
    while(searchBy[i] != '\0')
    {
        toupper(searchBy[i]);
        i++;
    }

    if (strcmp("PIN CODE",searchBy) == 0)
    {
        bubbleSort_PIN(temp);
        
        
    }
    else if (strcmp("DISTRICT",searchBy) == 0)
    {
        bubbleSort_district(temp);
           
    }
    i = 0;
    while (i < center_record_size - 1)
    {
        printf("%lld %s %s %lld %s ",(*(temp+i)).id, ((*(temp+i)).address), ((*(temp+i)).district), ((*(temp+i)).PIN),((*(temp+i)).center_type));
        printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(temp+i)).vaccine.covaxin,(*(temp+i)).vaccine.covishield,(*(temp+i)).vaccine.sputnik,(*(temp+i)).vaccine.zydus,(*(temp+i)).vaccine.Pfizer,(*(temp+i)).vaccine.moderna);
        i++;
    }
    printf("\n");
}

void getCenter(char input1[], char input2[])
{
    int i = 0;
    char searchBy[strlen(input1) + 1];
    char search[strlen(input2) + 1];
    while(input1[i] != '\0')
    {
        searchBy[i] = toupper(input1[i]);
        i++;
    }
    searchBy[i] = '\0';
    i = 0;
    while(input2[i] != '\0')
    {
        search[i] = toupper(input2[i]);
        i++;
    }
    search[i] = '\0';
    
    if(strcmp("CENTER ID",searchBy) == 0)
    {
        char *ptr;
        long long search_for;
        search_for = strtoll(search, &ptr, 10);
        i = 0;
        while (i < center_record_size - 1)
        {
            if((*(center + i)).id == search_for)
            {
                printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
            }
            i++;
        }
        
    }
    else if(strcmp("DISTRICT",searchBy) == 0)
    {
        i = 0;
        while (i < center_record_size - 1)
        {
            if(strcmp((*(center + i)).district, search) == 0)
            {
                printf("CENTER id = %lld Address = %s District = %s PIN = %lld CENTER TYPE = %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
            }
            i++;
            
        }
    }
    else if(strcmp("PIN CODE",searchBy) == 0)
    {
        char *ptr;
        long long search_for;
        search_for = strtoll(search, &ptr, 10);
        i = 0;
        while (i < center_record_size - 1)
        {
            if((*(center + i)).PIN == search_for)
            {
                printf("CENTER id = %lld Address = %s District = %s PIN = %lld CENTER TYPE = %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
            }
            i++;
        }
    }
    else if(strcmp("CENTER TYPE",searchBy) == 0)
    {
        i = 0;
        while (i < center_record_size - 1)
        {
            if(strcmp((*(center + i)).center_type, search) == 0)
            {
                printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
            }
            i++;
        }
    }
    else if(strcmp("VACCINE TYPE",searchBy) == 0)
    {
        if(strcmp("COVAXIN",search) == 0)
        {
            
            i = 0;
            int n = 0;
            while (i < center_record_size - 1)
            {
                if(((&(*(center + i)).vaccine.covaxin) + n) > 0)
                {
                    printf("%lld has %lld doses\n",(*(center + i)).id, (*(center + i)).vaccine.covaxin);
                }
                i++;
            }
        }
        else if(strcmp("COVISHIELD",search) == 0)
        {
            printf("\nDOUBLE YES\n");
            i = 0;
            while (i < center_record_size - 1)
            {
                if((*(center + i)).vaccine.covishield > 0)
                {
                    printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcmp("SPUTNIK",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((*(center + i)).vaccine.Pfizer > 0)
                {
                    printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcmp("ZYDUS",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((*(center + i)).vaccine.zydus > 0)
                {
                    printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcmp("PFIZER",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((*(center + i)).vaccine.moderna > 0)
                {
                    printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcmp("MODERNA",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((*(center + i)).vaccine.sputnik > 0)
                {
                    printf("%lld %s %s %lld %s ",(*(center+i)).id, ((*(center+i)).address), ((*(center+i)).district), ((*(center+i)).PIN),((*(center+i)).center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(*(center+i)).vaccine.covaxin,(*(center+i)).vaccine.covishield,(*(center+i)).vaccine.sputnik,(*(center+i)).vaccine.zydus,(*(center+i)).vaccine.Pfizer,(*(center+i)).vaccine.moderna);
                }
                i++;
            }
        }
    }
}

void BookAppointment(long long beneficiary_id, long long center_id, char vaccine_type[])
{
    int i = 0, flag = 0;
    while (i < center_record_size - 1 && flag == 0)
    {
        if(beneficiary_id == (beneficiary+i)->id)
        {
            flag = 1;
            (beneficiary+i)->appointment.center_id = center_id;
            strcpy((beneficiary+i)->appointment.vaccine_type,vaccine_type);
            if((beneficiary+i)->appointment.first_appointment_status == 'n')
            {
                (beneficiary+i)->appointment.first_appointment_status = 'y';
            }
            else if((beneficiary+i)->appointment.first_appointment_status == 'n')
            {
                (beneficiary+i)->appointment.second_appointment_status = 'y';
            }
            else
            {
                printf("Beneficiary has completed both doses\n");
            }
        }
    }
    if(flag == 0)
    {
        printf("Beneficiary not found\n");
    }
    
}

void CancelAppointment(long long beneficiary_id)
{
    int i = 0, flag = 0;
    while (i < center_record_size - 1 && flag == 0)
    {
        if(beneficiary_id == (beneficiary+i)->id)
        {
            flag = 1;
            if((beneficiary+i)->appointment.first_appointment_status == 'y')
            {
                (beneficiary+i)->appointment.first_appointment_status = 'n';
            }
            else if((beneficiary+i)->appointment.second_appointment_status == 'y')
            {
                (beneficiary+i)->appointment.second_appointment_status = 'n';
            }
            else
            {
                printf("Beneficiary has not booked any appointment\n");
            }
        }
    }
    if(flag == 0)
    {
        printf("beneficiary not found\n");
    }
    
}

void removeCentre(long long center_id)
{
    int flag = 0,i = 0;
    while(i < center_record_size && flag == 0) // finding the index at which data should be inserted
    {
        if((*(center + i)).id == center_id)
        {
            int j = i;
            while(j < center_record_size - 2) // shifting records to right from sorting position
            {
                (*(center + j)) = (*(center + j + 1));
                i++;
            }
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    // i = 0;
    // while (i < beneficiary_record_size)
    // {
    //     printf("%lld %s %s %d\n",((center+i)->id), ((center+i)->name), ((center+i)->gender), ((center+i)->year_of_birth));
    //     i++;
    // }
    // printf("\n");
    center_record_size -= 1;
    center = realloc(center, center_record_size*sizeof(struct Center));
    set_default_center(center + (center_record_size -1));
}

void removeBeneficiary(long long beneficiary_id)
{
    int flag = 0,i = 0;
    while(i < beneficiary_record_size && flag == 0) // finding the index at which data should be inserted
    {
        if((*(beneficiary + i)).id == beneficiary_id)
        {
            char ch;
            printf("\nDo you want to update year of birth? press (y/n): ");
            scanf("%c",ch);
            if(ch == 'y')
            {
                printf("\nEnter the year of birth:");
                scanf("%d",beneficiary->year_of_birth);
            }
            printf("\nDo you want to update name? press (y/n): ");
            scanf("%c",ch);
            if(ch == 'y')
            {
                printf("\nEnter the name:");
                scanf("%[^\n]s",beneficiary->year_of_birth);
            }
            
            printf("\nDo you want to update gender? press (y/n): ");
            scanf("%c",ch);
            if(ch == 'y')
            {
                printf("\nEnter the new year of birth:");
                scanf("%d",beneficiary->gender);
            }
        }
        else
        {
            i++;
        }
    }
    // i = 0;
    // while (i < beneficiary_record_size)
    // {
    //     printf("%lld %s %s %d\n",((beneficiary+i)->id), ((beneficiary+i)->name), ((beneficiary+i)->gender), ((beneficiary+i)->year_of_birth));
    //     i++;
    // }
    // printf("\n");
    beneficiary_record_size -= 1;
    beneficiary = realloc(beneficiary, beneficiary_record_size*sizeof(struct Beneficiary));
    set_default_Bene(beneficiary + (beneficiary_record_size -1));
}

void main(void)
{

    
    beneficiary = (struct Beneficiary *)malloc(beneficiary_record_size * sizeof(struct Beneficiary));
    set_default_Bene(beneficiary + (beneficiary_record_size -1));

    center = (struct Center *)malloc(center_record_size * sizeof(struct Center));
    set_default_center(center + (center_record_size -1));
    addNewBeneficiary("Happy Singh", "male", 2016);
    addNewBeneficiary("sanjit patel", "male", 1976);
    addNewBeneficiary("Aniket jivoji", "female", 1932);
    addNewBeneficiary("rgegre jivobgdhji", "female", 1986);
    
    set_default_vaccine(&vaccine);
    (&vaccine)->covaxin = 31;
    (&vaccine)->covishield = 374;
    (&vaccine)->sputnik = 372;
    (&vaccine)->zydus = 23;
    (&vaccine)->Pfizer = 34;
    (&vaccine)->moderna = 342;
    addNewCenter(67902, "maruthi nagar statue", "ka1rwar", 388221, "private", (&vaccine));
    set_default_vaccine((&vaccine));
    (&vaccine)->covaxin = 531;
    (&vaccine)->covishield = 74;
    (&vaccine)->sputnik = 72;
    (&vaccine)->zydus = 86;
    (&vaccine)->Pfizer = 97;
    (&vaccine)->moderna = 2;
    addNewCenter(74290, "aaaad hghawr gwy84", "shanaya", 568781, "private", (&vaccine));
    set_default_vaccine((&vaccine));
    (&vaccine)->covaxin = 341;
    (&vaccine)->covishield = 874;
    (&vaccine)->sputnik = 382;
    (&vaccine)->zydus = 873;
    (&vaccine)->Pfizer = 84;
    (&vaccine)->moderna = 72;
    addNewCenter(34883, "uwyefoh awe rfwr u", "simplistic", 268221, "government", (&vaccine));
    set_default_vaccine((&vaccine));
    (&vaccine)->covaxin = 9331;
    (&vaccine)->covishield = 4374;
    (&vaccine)->sputnik = 772;
    (&vaccine)->zydus = 83;
    (&vaccine)->Pfizer = 14;
    (&vaccine)->moderna = 72;
    addNewCenter(83708, "n804ur8y4cnb yr y8", "scyhu", 438221, "government", (&vaccine));
    set_default_vaccine(&vaccine);
    (&vaccine)->covaxin = 424;
    (&vaccine)->covishield = 141;
    (&vaccine)->sputnik = 41;
    (&vaccine)->zydus = 51;
    (&vaccine)->Pfizer = 513;
    (&vaccine)->moderna = 151;
    addNewCenter(56850, "yguyir y843ty7y 4t", "ytyiomm", 868221, "government", (&vaccine));
    set_default_vaccine((&vaccine));
    (&vaccine)->covaxin = 390;
    (&vaccine)->covishield = 2747;
    (&vaccine)->sputnik = 5723;
    (&vaccine)->zydus = 75;
    (&vaccine)->Pfizer = 385;
    (&vaccine)->moderna = 358;
    addNewCenter(87508, "y9 y843ty7y 4yygft", "rifyo", 128221, "government", (&vaccine));
    // printf("Printing according to PIN CODE\n");
    // EnlistSortedCenters("center id");
    getCenter("vaccine type", "covishield");
    free(beneficiary);
    free(center);
}
