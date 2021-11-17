#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>
#include<stdbool.h>
#define AGE_RESTRICTION 18
#define LOWER 10000
#define UPPER 99999


// creating required structs
struct Appointment
{
    char first_appointment_status;
    char second_appointment_status;
    long long first_appointment_center_id;
    long long second_appointment_center_id;
    char vaccine_type[12];
};

struct Beneficiary
{
    long long id;
    int year_of_birth;
    int number_of_doses_taken;
    struct Appointment appointment;
    char name[50];
    char gender[10];
};

struct District
{
    char district[30];
    int count;
};

struct Vaccine
{
    long long covaxin, covishield, sputnik, zydus, Pfizer, moderna;
    long long covaxin_cost, covishield_cost, sputnik_cost, zydus_cost, Pfizer_cost, moderna_cost;
};

struct Center
{
    long long PIN;
    long long id;
    char address[94];
    struct Vaccine vaccine;
    char district[30];
    char center_type[12];
    long long income;
};

struct seniorCitizen
{
    char name[50];
    long long center_id;
};

// Declarind and initializing some global variables
struct Beneficiary* beneficiary;
struct Center* center;
struct District *districts;
int beneficiary_record_size = 1;
int center_record_size = 1;
int district_record_size = 1;
struct Vaccine vaccine;
char temporary; //Buffer input for helping with input with spaces

// swaps two center struct
void swap_struct_center(struct Center *a, struct Center *b)
{
    struct Center temp = *a;
    *a = *b;
    *b = temp;
}

// function for setting struct variables to default value
void set_default_Bene(struct Beneficiary *B)
{
    B->id = 100000;
    B->year_of_birth = 2020;
    B->number_of_doses_taken = 0;
    B->appointment.first_appointment_center_id = 0;
    B->appointment.second_appointment_center_id = 0;
    B->appointment.first_appointment_status = 'n';
    B->appointment.second_appointment_status = 'n';
}

void set_default_center(struct Center *center)
{
    center->id = LLONG_MAX;
    center->PIN = 0;
    center->income = 0;
    center->vaccine.covaxin = 0;
    center->vaccine.covishield = 0;
    center->vaccine.sputnik = 0;
    center->vaccine.zydus = 0;
    center->vaccine.Pfizer = 0;
    center->vaccine.moderna = 0;
};

void set_default_District(struct District *districts)
{
    districts->count = 0;
}

void set_default_vaccine(struct Vaccine *vaccine)
{

    vaccine->covaxin = 0;
    vaccine->covaxin_cost = 755;
    vaccine->covishield = 0;
    vaccine->covishield_cost = 455;
    vaccine->sputnik = 0;
    vaccine->sputnik_cost = 400;
    vaccine->zydus = 0;
    vaccine->zydus_cost = 577;
    vaccine->Pfizer = 0;
    vaccine->Pfizer_cost = 857;
    vaccine->moderna = 0;
    vaccine->moderna_cost = 567;
};

// Function for adding new beneficiary
void addNewBeneficiary(char name[], char gender[], int year_of_birth)
{
    // Generating random 5 digit numbers
    long long random = rand();
    long long generated_id = (random % (UPPER - LOWER + 1)) + LOWER;
    int flag = 0, storing_index = 0, i = 0;
    // Checking uniqueness of the generated id
    while(i < beneficiary_record_size) 
    {
        // if not unique another id is generated
        if(generated_id == ((beneficiary + i)->id))
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
    // finding the index at which data should be inserted
    while(i < beneficiary_record_size && flag == 0) 
    {
        if((beneficiary + i)->id > generated_id)
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
     // shifting records to right from sorting position
    while(i > storing_index)
    {
        (*(beneficiary + i)) = (*(beneficiary + i - 1));
        i--;
    }
    // copying records
    (beneficiary+storing_index)->id = generated_id;
    strcpy((beneficiary + storing_index)->name,name);
    strcpy((beneficiary + storing_index)->gender,gender);
    (beneficiary + storing_index)->year_of_birth = year_of_birth;
    // printing
    i = 0;
    while (i < beneficiary_record_size)
    {
        printf("Beneficiary ID = %lld, name =  %s, gender = %s, year of birth = %d\n",((beneficiary+i)->id), ((beneficiary+i)->name), ((beneficiary+i)->gender), ((beneficiary+i)->year_of_birth));
        i++;
    }
    printf("\n");
    beneficiary_record_size += 1;
    beneficiary = realloc(beneficiary, beneficiary_record_size*sizeof(struct Beneficiary));
    set_default_Bene(beneficiary + (beneficiary_record_size -1));
    
}

// Function for adding new Center 
void addNewCenter(long long center_id, char address[], char district[], long long PIN, char center_type[], struct Vaccine *vaccine)
{
    int flag = 0, storing_index = 0, i = 0;
    while(i < center_record_size && flag == 0) // finding the index at which data should be inserted
    {
        
        if((center + i)->id > center_id)
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
    // copying records
    (center + storing_index)->id = center_id;
    strcpy((center + storing_index)->address,address);
    strcpy((center + storing_index)->district,district);
    strcpy((center + storing_index)->center_type,center_type);
    (center + storing_index)->PIN = PIN;
    ((center+storing_index)->vaccine).covaxin = vaccine->covaxin;
    ((center+storing_index)->vaccine).covishield = vaccine->covishield;
    ((center+storing_index)->vaccine).Pfizer = vaccine->Pfizer;
    ((center+storing_index)->vaccine).sputnik = vaccine->sputnik;
    ((center+storing_index)->vaccine).zydus = vaccine->zydus;
    ((center+storing_index)->vaccine).moderna = vaccine->moderna;
    // printing
    i = 0;
    while (i < center_record_size)
    {
        printf("%lld %s %s %lld %s ",(center+i)->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
        printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",((center+i)->vaccine).covaxin, ((center+i)->vaccine).covishield, ((center+i)->vaccine).sputnik,((center+i)->vaccine).zydus,((center+i)->vaccine).Pfizer,((center+i)->vaccine).moderna);
        i++;
    }
    printf("\n");
    center_record_size++;
    center = realloc(center, center_record_size*sizeof(struct Center));
    set_default_center(center + (center_record_size -1));
    
}

// function for adding new districts and to maintain count of vaccines booked in each diistrict
void addNewDistrict(char district_name[])
{
    int flag = 1, i = 0;
    while(i < district_record_size - 1) // Checking uniqueness of disrict name
    {
        // count is increased for the district if name is already present
        if(strcasecmp(district_name ,(districts + i)->district) == 0)
        {
            ((districts + i)->count) = ((districts + i)->count) + 1;
            flag = 0;
        }
        
        i++;

    }
    // if the name is unique then it is added as new record
    if(flag == 1)
    {
        strcpy((districts + district_record_size - 1)->district, district_name);
        ((districts + district_record_size - 1)->count) = ((districts + district_record_size - 1)->count) + 1;
        district_record_size += 1;
        districts = realloc(districts, district_record_size*sizeof(struct District));
        set_default_District(districts + (district_record_size -1));
    }
}


// Sorting function using merge algorithm
void merge(struct Center *a, int l, int m, int r, int sortBy)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Center L[n1], R[n2];
    // copying to temporary array
    for (i = 0; i < n1; i++)
    {
        L[i] = *(a + l + i);
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = *(a + m + 1 + j);
    }
    i = 0; 
    j = 0; 
    k = l; 
    // sorting based on input
    if(sortBy == 0)
    {
        while (i < n1 && j < n2)
        {
            if (L[i].PIN <= R[j].PIN)
            {
                *(a + k) = L[i];
                i++;
            }
            else {
                *(a + k) = R[j];
                j++;
            }
            k++;
        }
    }
    else if(sortBy == 1)
    {
        while (i < n1 && j < n2)
        {
            if (strcasecmp(L[i].district, R[j].district) <= 0)
            {
                *(a + k) = L[i];
                i++;
            }
            else {
                *(a + k) = R[j];
                j++;
            }
            k++;
        }
    }
    else if(sortBy == 2)
    {
        while (i < n1 && j < n2)
        {
            if (L[i].id <= R[j].id)
            {
                *(a + k) = L[i];
                i++;
            }
            else {
                *(a + k) = R[j];
                j++;
            }
            k++;
        }
    }
    while (i < n1) {
        *(a + k) = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        *(a + k) = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Center *a, int l, int r,int sort_by)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m, sort_by);
        mergeSort(a, m + 1, r, sort_by);
        merge(a, l, m, r, sort_by);
    }
}

// Function for generating sorted list of centers
void EnlistSortedCenters(char sortBy[])
{
    // creating a temp array of struct centers
    struct Center *temp;
    temp = (struct Center *)malloc(center_record_size * sizeof(struct Center));
    //copying every struct
    for(int i = 0; i < center_record_size; i++)
    {
        *(temp + i) = *(center + i);
    }
    int flag = 0;
    // input decides the sorting option
    if (strcasecmp("PIN CODE",sortBy) == 0)
    {
        mergeSort(temp, 0, center_record_size - 2, 0); 
        flag = 1;      
    }
    else if (strcasecmp("DISTRICT",sortBy) == 0)
    {
        mergeSort(temp, 0, center_record_size - 2, 1);
        flag = 1;   
    }
    else if (strcasecmp("center ID",sortBy) == 0)
    {
        flag = 1;   
    }
    // if the input is valid and the list is sorted then print
    if(flag == 1)
    {
        int i = 0;
        while (i < center_record_size - 1)
        {
            printf("%lld %s %s %lld %s ",(temp+i)->id, (temp+i)->address, (temp+i)->district, (temp+i)->PIN,(temp+i)->center_type);
            printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(temp+i)->vaccine.covaxin,(temp+i)->vaccine.covishield,(temp+i)->vaccine.sputnik,(temp+i)->vaccine.zydus,(temp+i)->vaccine.Pfizer,(temp+i)->vaccine.moderna);
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Enter a valid parameter\n");
    }
}

// Function for generating list of centers based on the search parameter and search keyword
void getCenter(char searchBy[])
{
    int i = 0;    
    if(strcasecmp("CENTER ID",searchBy) == 0)
    {
        long long search_for;
        printf("Enter center ID:");
        scanf("%lld",&search_for);
        i = 0;
        while (i < center_record_size - 1)
        {
            if((center + i)->id == search_for)
            {
                printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
            }
            i++;
        }
    }
    else if(strcasecmp("DISTRICT",searchBy) == 0)
    {
        char search[20],temp;
        printf("Enter district:");
        scanf("%s",search);
        i = 0;
        while (i < center_record_size - 1)
        {
            if(strcasecmp((center + i)->district, search) == 0)
            {
                printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
            }
            i++;
            
        }
    }
    else if(strcasecmp("PIN CODE",searchBy) == 0)
    {
        printf("Enter Pin Code:");
        long long search_for;
        scanf("%lld",&search_for);
        i = 0;
        while (i < center_record_size - 1)
        {
            if((center + i)->PIN == search_for)
            {
                printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
            }
            i++;
        }
    }
    else if(strcasecmp("CENTER TYPE",searchBy) == 0)
    {
        char search[20];
        printf("Enter center type:");
        scanf("%s",search);
        i = 0;
        while (i < center_record_size - 1)
        {
            if(strcasecmp((center + i)->center_type, search) == 0)
            {
                printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
            }
            i++;
        }
    }
    else if(strcasecmp("VACCINE TYPE",searchBy) == 0)
    {
        printf("Enter vaccine type:");
        char search[20];
        scanf("%s",search);
        if(strcasecmp("COVAXIN",search) == 0)
        {
            
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.covaxin > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcasecmp("COVISHIELD",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.covishield > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcasecmp("SPUTNIK",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.sputnik > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcasecmp("ZYDUS",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.zydus > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcasecmp("PFIZER",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.Pfizer > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else if(strcasecmp("MODERNA",search) == 0)
        {
            i = 0;
            while (i < center_record_size - 1)
            {
                if((center + i)->vaccine.moderna > 0)
                {
                    printf("%lld %s %s %lld %s ",((center+i))->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
                    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
                }
                i++;
            }
        }
        else
        {
            printf("Enter a valid input\n"); // if vaccine name is invalid
        }
    }
    else
    {
        printf("Enter a valid input\n"); // if search parameter is invalid
    }
}

// Function for booking an appointment
void BookAppointment(long long beneficiary_id, long long center_id, char vaccine_type[])
{
    int age;
    printf("Enter the age:");
    scanf("%d",&age);
    // people with age greater than 18 are allowed to book for vaccine
    if(age > 18)
    {
        int i = 0, flag = 0, booking_status = 0, j = 0,flag1 = 0;
        // finding beneficiary id and then checking if vaccines are available
        while (j < beneficiary_record_size - 1 && flag == 0)
        {
            if(beneficiary_id == (beneficiary+j)->id)
            {
                // gives appointment without confirmation
                strcpy((beneficiary+j)->appointment.vaccine_type,vaccine_type);
                if((beneficiary+j)->appointment.first_appointment_status == 'n')
                {
                    (beneficiary+j)->appointment.first_appointment_status = 'y';
                    (beneficiary+j)->appointment.first_appointment_center_id = center_id;
                    booking_status = 1;
                    printf("First appointment of %lld has been processed\n",(beneficiary+j)->id);
                }
                if(((beneficiary+j)->appointment.second_appointment_status == 'n') && booking_status != 1)
                {
                    (beneficiary+j)->appointment.second_appointment_status = 'y';
                    (beneficiary+j)->appointment.second_appointment_center_id = center_id;
                    booking_status = 1;
                    printf("Second appointment of %lld has been processed\n",(beneficiary+j)->id);
                }
                // if the vaccine is booked checking for confirmation
                if(booking_status != 1)
                {
                    printf("Beneficiary has completed both doses\n");
                    flag = 1;
                }
                else
                {
                    i = 0;
                    while (i < center_record_size - 1 && flag == 0)
                    {                        
                        // finding center in which the vaccine was booked
                        if(center_id == (center+i)->id)
                        {
                            flag = 1;
                            // for the chosen vaccine type checking the availability of the vaccine in the center
                            // if not available then booking is cancelled by activating flag1
                            // if it is available then booking is confirmed
                            if(strcasecmp("covaxin", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.covaxin == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.covaxin = (center + i)->vaccine.covaxin - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.covaxin_cost;
                                }
                            }
                            else if(strcasecmp("covishield", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.covishield == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.covishield = (center + i)->vaccine.covishield - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.covishield_cost;
                                }
                            }
                            else if(strcasecmp("sputnik", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.sputnik == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.sputnik = (center + i)->vaccine.sputnik - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.sputnik_cost;
                                }
                            }
                            else if(strcasecmp("Pfizer", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.Pfizer == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.Pfizer = (center + i)->vaccine.Pfizer - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.Pfizer_cost;
                                }
                            }
                            else if(strcasecmp("zydus", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.zydus == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.zydus = (center + i)->vaccine.zydus - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.zydus_cost;
                                }
                            }
                            else if(strcasecmp("moderna", vaccine_type) == 0)
                            {
                                if((center + i)->vaccine.moderna == 0)
                                {
                                    printf("vaccine not available\n");
                                    flag1 = 1;
                                }
                                else
                                {
                                    (center + i)->vaccine.moderna = (center + i)->vaccine.moderna - 1;
                                    (center + i)->income = (center + i)->income + (center + i)->vaccine.moderna_cost;
                                }
                            }
                            else
                            {
                                printf("Enter valid vaccine type\n");
                            }

                            if(flag1 == 1)
                            {
                                if(((beneficiary+j)->appointment.second_appointment_status == 'y'))
                                {
                                    (beneficiary+j)->appointment.second_appointment_status = 'n';
                                    (beneficiary+j)->appointment.second_appointment_center_id = 0;
                                    printf("Second appointment of %lld has been cancelled\n",(beneficiary+j)->id);
                                }
                                else if((beneficiary+j)->appointment.first_appointment_status == 'y')
                                {
                                    (beneficiary+j)->appointment.first_appointment_status = 'n';
                                    (beneficiary+j)->appointment.first_appointment_center_id = 0;
                                    printf("First appointment of %lld has been cancelled\n",(beneficiary+j)->id);
                                }
                                
                            }
                            else if(flag1 == 0)
                            {
                                printf("Booking Confirmed\n");
                                // The district in which the vaccine was booked is added to list and count is increased
                                addNewDistrict((center + i)->district); 
                            }
                            
                        }
                        i++;
                    }
                }
            }
            j++;
        }
        if(booking_status == 0)
        {
            printf("Beneficiary not found\n");
        }
        if(flag == 0 && booking_status == 1)
        {
            printf("Center not found\n");
            if(((beneficiary+j - 1)->appointment.second_appointment_status == 'y'))
            {
                (beneficiary+j - 1)->appointment.second_appointment_status = 'n';
                (beneficiary+j - 1)->appointment.second_appointment_center_id = 0;
                printf("Second appointment of %lld has been cancelled\n",(beneficiary+j - 1)->id);
            }
            else if((beneficiary+j - 1)->appointment.first_appointment_status == 'y')
            {
                (beneficiary+j - 1)->appointment.first_appointment_status = 'n';
                (beneficiary+j - 1)->appointment.first_appointment_center_id = 0;
                printf("First appointment of %lld has been cancelled\n",(beneficiary+j - 1)->id);
            }
        }
    }
    else
    {
        printf("Age should be greater than 18\n");
    }
    
}

// Function for cancelling appointment
void CancelAppointment(long long beneficiary_id)
{
    int i = 0, flag = 0;
    while (i < beneficiary_record_size - 1 && flag == 0)
    {
        // finding beneficiary
        if(beneficiary_id == (beneficiary+i)->id)
        {
            // cancelling the last booked appointment
            flag = 1;
            if((beneficiary+i)->appointment.second_appointment_status == 'y')
            {
                (beneficiary+i)->appointment.second_appointment_status = 'n';
                printf("Beneficiary second appointment cancelled\n");
            }
            else if((beneficiary+i)->appointment.first_appointment_status == 'y')
            {
                (beneficiary+i)->appointment.first_appointment_status = 'n';
                printf("Beneficiary first appointment cancelled\n");
            }
            else
            {
                // if no appointment was booked
                printf("Beneficiary has not booked any appointment\n");
            }
        }
        i++;
    }
    if(flag == 0)
    {
        printf("beneficiary not found\n");
    }
        

    
}

// function to remove beneficiary from the list
void removeBeneficiary(long long beneficiary_id)
{
    int flag = 0,i = 0;
    // removing beneficiary from the list
    while(i < beneficiary_record_size -1 && flag == 0) 
    {
        if((beneficiary + i)->id == beneficiary_id)
        {
            int j = i;
            while(j < beneficiary_record_size - 2) 
            {
                (*(beneficiary + j)) = (*(beneficiary + j + 1));
                j++;
            }
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    // if the beneficiary is found and removed then canccelling all appointments
    if(flag == 1)
    {
        beneficiary_record_size -= 1;
        beneficiary = realloc(beneficiary, beneficiary_record_size*sizeof(struct Center));
        set_default_Bene(beneficiary + (beneficiary_record_size -1));
        i = 0;
        while (i < beneficiary_record_size - 1)
        {
            printf("Beneficiary ID = %lld, name =  %s, gender = %s, year of birth = %d\n",((beneficiary+i)->id), ((beneficiary+i)->name), ((beneficiary+i)->gender), ((beneficiary+i)->year_of_birth));
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Beneficiary not found\n");
    }
}

// Function to remove center
void removeCentre(long long center_id)
{
    // removing center from the list
    int flag = 0,i = 0, removed = 0;
    while(i < center_record_size && flag == 0)
    {
        if((center + i)->id == center_id)
        {
            int j = i;
            while(j < center_record_size - 2)
            {
                (*(center + j)) = (*(center + j + 1));
                j++;
            }
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    // if the center is found and removed then cancelling all appointments
    if(flag == 1)
    {
        i = 0;
        while(i < beneficiary_record_size - 1)
        {
            if((beneficiary+i)->appointment.first_appointment_center_id == center_id)
            {
                if((beneficiary+i)->appointment.first_appointment_status == 'y')
                {
                    (beneficiary+i)->appointment.first_appointment_status = 'n';
                    (beneficiary+i)->appointment.first_appointment_center_id = 0;
                    flag = 1;
                    printf("First appointment of %lld has been confirmed\n",beneficiary->id);
                }
            }
            if((beneficiary+i)->appointment.second_appointment_center_id == center_id)
            {
                if((beneficiary+i)->appointment.second_appointment_status == 'y')
                {
                    (beneficiary+i)->appointment.second_appointment_status = 'n';
                    (beneficiary+i)->appointment.second_appointment_center_id = 0;
                    flag = 1;
                    printf("Second appointment of %lld has been confirmed\n",beneficiary->id);
                }
            }
            i++;
        }
        // decreasing center size
        center_record_size -= 1;
        center = realloc(center, center_record_size*sizeof(struct Center));
        set_default_center(center + (center_record_size -1));
        i = 0;
        while (i < center_record_size - 1)
        {
            printf("%lld %s %s %lld %s ", (center+i)->id, (center+i)->address, (center+i)->district, (center+i)->PIN,(center+i)->center_type);
            printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",((center+i)->vaccine).covaxin, ((center+i)->vaccine).covishield, ((center+i)->vaccine).sputnik,((center+i)->vaccine).zydus,((center+i)->vaccine).Pfizer,((center+i)->vaccine).moderna);
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("center not found\n");
    }
}

// Function for updating beneficiary information
void UpdateBeneficiaryInfo(long long beneficiary_id)
{
    int flag = 0,i = 0, input;
    while(i < beneficiary_record_size - 1 && flag == 0)
    {
        if((beneficiary + i)->id == beneficiary_id)
        {
            while(flag == 0)
            {
                // Asking for choice and editing accordingly
                printf("Name = %s, year of birth = %d, gender = %s\n\n",(beneficiary + i)->name,(beneficiary + i)->year_of_birth,(beneficiary + i)->gender);
                printf("Press 1 for updating year of Birth\n");
                printf("Press 2 for updating gender\n");
                printf("Press 3 for updating name\n");
                printf("Press 4 to exit\nGive you input:");
                scanf("%d",&input);
                if(input == 1)
                {
                    printf("Enter the year of birth:");
                    scanf("%d",&((beneficiary + i)->year_of_birth));
                }
                else if(input == 2)
                {
                    printf("Enter the gender:");
                    scanf("%s",((beneficiary + i)->gender));
                }
                else if(input == 3)
                {
                    printf("Enter the name:");
                    scanf("%c",&temporary);
                    scanf("%[^\n]%*c",((beneficiary + i)->name));
                }
                else if(input == 4)
                {
                    printf("You selected to exit\n");
                    flag = 1;
                }
                else
                {
                    printf("please enter a valid input\n");
                }
            }
            
        }
        else
        {
            i++;
        }
    }
    // if beneficiary is found and edited then printing information
    if(flag == 1)
    {
        i = 0;
        while (i < beneficiary_record_size - 1)
        {
            printf("%lld %s %s %d\n",((beneficiary+i)->id), ((beneficiary+i)->name), ((beneficiary+i)->gender), ((beneficiary+i)->year_of_birth));
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Beneficiary not found\n");
    }
}

// Function for updating center information
void UpdateCenterInfo(long long center_id)
{
    int flag = 0,i = 0, input;
    while(i < center_record_size - 1 && flag == 0)
    {
        if((center + i)->id == center_id)
        {
            while(flag == 0)
            {
                // Asking for choice and editing accordingly
                printf("%lld %s %s %lld %s ", (center+i)->id, (center+i)->address, (center+i)->district, (center+i)->PIN,(center+i)->center_type);
                printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",((center+i)->vaccine).covaxin, ((center+i)->vaccine).covishield, ((center+i)->vaccine).sputnik,((center+i)->vaccine).zydus,((center+i)->vaccine).Pfizer,((center+i)->vaccine).moderna);
                printf("Press 1 for updating PIN\n");
                printf("Press 2 for address\n");
                printf("Press 3 for Center ID\n");
                printf("Press 4 for Vaccine availability information\n");
                printf("Press 5 for District\n");
                printf("Press 6 for Center Type\n");
                printf("Press 7 to exit\nGive input:");
                scanf("%d",&input);
                if(input == 1)
                {
                    printf("Enter the PIN code:");
                    scanf("%lld",&((center + i)->PIN));
                }
                else if(input == 2)
                {
                    printf("Enter the address:");
                    scanf("%c",&temporary);
                    scanf("%[^\n]%*c",((center + i)->address));
                }
                else if(input == 3)
                {
                    printf("Enter the center ID:");
                    long long temp;
                    scanf("%lld",&temp);
                    ((center + i)->id) = temp;
                    mergeSort(center, 0, center_record_size - 2, 2);
                    int j = 0, flag1 = 0;
                    while(j < center_record_size && flag == 0)
                    {
                        if((center + j)->id == temp)
                        {
                            i = j;
                            flag1 = 1;
                        }
                        j++;
                    }
                    
                }
                else if(input == 4)
                {
                    printf("Press 1 for covaxin data\n");
                    printf("Press 2 for covishield data\n");
                    printf("Press 3 for sputnik data\n");
                    printf("Press 4 for zydus data\n");
                    printf("Press 5 for pfizer data\n");
                    printf("Press 6 for moderna\n");
                    scanf("%d",&input);
                    if(input == 1)
                    {
                        printf("Enter new covaxin data:");
                        scanf("%lld",&((center + i)->vaccine.covaxin));
                    }
                    else if(input == 2)
                    {
                        printf("Enter new covishield data:");
                        scanf("%lld",&((center + i)->vaccine.covishield));
                    }
                    else if(input == 3)
                    {
                        printf("Enter new sputnik data:");
                        scanf("%lld",&((center + i)->vaccine.sputnik));
                    }
                    else if(input == 4)
                    {
                        printf("Enter new zydus data:");
                        scanf("%lld",&((center + i)->vaccine.zydus));
                        
                    }
                    else if(input == 2)
                    {
                        printf("Enter new pfizer data:");
                        scanf("%lld",&((center + i)->vaccine.Pfizer));
                    }
                    else if(input == 6)
                    {
                        printf("Enter new moderna data:");
                        scanf("%lld",&((center + i)->vaccine.moderna));
                    }
                    else
                    {
                        printf("please enter a valid input\n");
                    }                  
                }
                else if(input == 5)
                {
                    printf("Enter the district:");
                    scanf("%s",((center + i)->district));
                }
                else if(input == 6)
                {
                    printf("Enter the center type:");
                    scanf("%s",((center + i)->center_type));
                }
                else if(input == 7)
                {
                    printf("You selected to exit\n");
                    printf("Changes have been Succesfully saved\n");
                    flag = 1;
                }
                else
                {
                    printf("please enter a valid input\n");
                }
            }
            
        }
        else
        {
            i++;
        }
    }
    // if center is found and edited then printing information
    if(flag == 1)
    {
        i = 0;
        while (i < center_record_size - 1)
        {
            printf("%lld %s %s %lld %s ", (center+i)->id, ((center+i)->address), ((center+i)->district), ((center+i)->PIN),((center+i)->center_type));
            printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",((center+i)->vaccine).covaxin, ((center+i)->vaccine).covishield, ((center+i)->vaccine).sputnik,((center+i)->vaccine).zydus,((center+i)->vaccine).Pfizer,((center+i)->vaccine).moderna);
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Center not found\n");
    }
}

// Finding center with maximum income
void MaxIncome()
{
    int i = 0;
    long long max = 0;
    struct Center temp;
    temp = *(center + i);
    while(i < center_record_size - 1) 
    {
        // checking is center is private as government centers do not generate any income
        if((strcasecmp((center + i)->center_type, "private")) == 0)
        {
            // finding last appearance of the max income
            if((center + i)->income >= max)
            {
                temp = *(center + i);
                max = (center + i)->income;
            }
        }
        
        i++;
    }
    // printing information of the center with highest income
    printf("Income Generated = %lld ID = %lld address = %s district = %s PIN = %lld center type = %s ",temp.income,temp.id, temp.address, temp.district, temp.PIN,temp.center_type);
    printf("Covaxin = %lld, Covishield = %lld, Sputnik = %lld, Zydus = %lld, Pfizer = %lld, Moderna = %lld\n",temp.vaccine.covaxin,temp.vaccine.covishield,temp.vaccine.sputnik,temp.vaccine.zydus,temp.vaccine.Pfizer,temp.vaccine.moderna);
    
}

// Function for generating availability report
void VaccineAvailabilityReport()
{
    // as after each appointment booked vaccine count is reduces the center data is the required list
    int i = 0;
    while(i < center_record_size - 1)
    {
        printf("Center %lld vaccine data:\n ",((center+i))->id);
        printf("Covaxin = %lld\n Covishield = %lld,\n Sputnik = %lld\n Zydus = %lld\n Pfizer = %lld\n Moderna = %lld\n\n",(center+i)->vaccine.covaxin,(center+i)->vaccine.covishield,(center+i)->vaccine.sputnik,(center+i)->vaccine.zydus,(center+i)->vaccine.Pfizer,(center+i)->vaccine.moderna);
        i++;
    }
}

// Function for generating District report
void DistrictReport()
{
    // prints every district and the count of vaccines booked
    int i = 0;
    while(i < district_record_size - 1)
    {
        printf("%s has %d vaccines booked\n",(districts + i)->district,(districts + i)->count);
        i++;
    }
}

// Function for checking if senior citizen have booked both doses at the same center
void SeniorCitizenIntersection(struct seniorCitizen *a, struct seniorCitizen *b,int sizeA, int sizeB)
{
    // struct a is array of senior citizens taking first dose
    // struct b is array of senior citizen taking second dose
    int i = 0, j = 0, flag = 0;
    while(i < sizeA)
    {
        j = 0;
        while(j < sizeB)
        {
            printf("%s %s %lld %lld\n",((a + i)->center_id, (b + j)->center_id),(a + i)->name,(b + j)->name );
            // checking if names are same
            if(strcasecmp((a + i)->name,(b + j)->name) == 0)
            {
                printf("compared\n");
                // if names are same then checking if center id is same
                if(((a + i)->center_id == (b + j)->center_id) )
                {
                    flag = 1;
                    printf("%s booked both doses at center %lld\n",(a + i)->name, (a + i)->center_id);
                }
            }
            j++;
        }
        i++;
    }
    if(flag == 0)
    {
        printf("No Senior Citizen booked both the doses in same center\n");
    }

}


void main(void)
{
    // alloting space to declared structs with intial size = 1
    beneficiary = (struct Beneficiary *)malloc(beneficiary_record_size * sizeof(struct Beneficiary));
    set_default_Bene(beneficiary + (beneficiary_record_size -1));

    center = (struct Center *)malloc(center_record_size * sizeof(struct Center));
    set_default_center(center + (center_record_size -1));

    districts = (struct District *)malloc(district_record_size * sizeof(struct District));
    set_default_District(districts + (district_record_size -1));

    int input;
    int exit_condition = 0;
    // running program until user wants to exit
    while(exit_condition == 0)
    {
        printf("Choose function:\n");
        printf("Enter 1 to add beneficiary\n");
        printf("Enter 2 to add center\n");
        printf("Enter 3 to enlist sorted array\n");
        printf("Enter 4 to get center\n");
        printf("Enter 5 to book appointment\n");
        printf("Enter 6 to cancel appointment\n");
        printf("Enter 7 to remove beneficiary\n");
        printf("Enter 8 to remove center\n");
        printf("Enter 9 to update beneficiary information\n");
        printf("Enter 10 to update center information\n");
        printf("Enter 11 to find the maximum income center\n");
        printf("Enter 12 to get vaccine availability report\n");
        printf("Enter 13 to distict report\n");
        printf("Enter 14 to senior citizen intersection\n");
        printf("Enter 15 to exit the program\n");
        printf("\nGive your input:");
        scanf("%d",&input);
        // performing action accorfing to the input given by user
        if(input == 1)
        {
            int year_of_birth;
            char name[100];
            char gender[10];
            scanf("%c",&temporary);
            printf("Enter the beneficiary name:");
            scanf("%[^\n]%*c",name);
            printf("Enter the beneficiary gender:");
            scanf("%s",gender);
            printf("Enter the beneficiary year of birth:");
            scanf("%d",&year_of_birth);
            addNewBeneficiary(name, gender,year_of_birth);
        }
        else if(input == 2)
        {
            long long PIN;
            char address[94];
            struct Vaccine vaccine;
            char district[30];
            char center_type[12];
            long long income;
            long long center_id;
            printf("Enter the center ID:");
            scanf("%lld",&center_id);
            printf("Enter the center address:");
            scanf("%c",&temporary);
            scanf("%[^\n]%*c",&address);
            printf("Enter the center district:");
            scanf("%s",&district);
            printf("Enter the center type:");
            scanf("%s",&center_type);
            printf("Enter center PIN code:");
            scanf("%lld",&PIN);
            printf("Enter number of covaxin:");
            scanf("%lld",&(vaccine.covaxin));
            printf("Enter number of covishield:");
            scanf("%lld",&(vaccine.covishield));
            printf("Enter number of Pfizer:");
            scanf("%lld",&(vaccine.Pfizer));
            printf("Enter number of sputnik:");
            scanf("%lld",&(vaccine.sputnik));
            printf("Enter number of zydus:");
            scanf("%lld",&(vaccine.zydus));
            printf("Enter number of moderna:");
            scanf("%lld",&(vaccine.moderna));
            addNewCenter(center_id, address, district,PIN, center_type,&vaccine);
        }
        else if(input == 3)
        {
            char searchBy[20];
            printf("Enter the parameter to sort by(Center ID/PIN code/District):");
            scanf("%c",&temporary);
            scanf("%[^\n]%*c",&searchBy);
            EnlistSortedCenters(searchBy);
        }
        else if( input == 4)
        {
            char searchBy[20];
            printf("Enter the parameter to list by(Center ID/District/PIN code/center type/vaccine type):");
            scanf("%c",&temporary);
            scanf("%[^\n]%*c",&searchBy);
            getCenter(searchBy);
        }
        else if(input == 5)
        {
            long long beneficiary_id, center_id;
            char vaccine_type[10];
            printf("Enter the beneficiary ID:");
            scanf("%lld",&(beneficiary_id));
            printf("Enter the center ID:");
            scanf("%lld",&center_id);
            printf("Enter the vaccine type:");
            scanf("%s",&vaccine_type);
            BookAppointment(beneficiary_id,center_id,vaccine_type);
        }
        
        else if(input == 6)
        {
            long long beneficiary_id;
            printf("Enter the beneficiary ID:");
            scanf("%lld",&beneficiary_id);
            CancelAppointment(beneficiary_id);
        }
        else if(input == 7)
        {
            long long beneficiary_id;
            printf("Enter the beneficiary ID:");
            scanf("%lld",&beneficiary_id);
            removeBeneficiary(beneficiary_id);
        }
        else if(input == 8)
        {
            long long center_id;
            printf("Enter the center ID:");
            scanf("%lld",&center_id);
            removeCentre(center_id);
        }
        else if(input == 9)
        {
            long long beneficiary_id;
            printf("Enter the beneficiary ID:");
            scanf("%lld",&beneficiary_id);
            UpdateBeneficiaryInfo(beneficiary_id);
        }
        else if(input == 10)
        {
            long long center_id;
            printf("Enter the center ID:");
            scanf("%lld",&center_id);
            UpdateCenterInfo(center_id);
        }
        else if(input == 11)
        {
            MaxIncome();
        }
        else if(input == 12)
        {
            VaccineAvailabilityReport();
        }
        else if(input == 13)
        {
            DistrictReport();
        }
        else if(input == 14)
        {
            struct seniorCitizen *A;
            struct seniorCitizen *B;
            int sizeA = 1, sizeB = 1;
            A = (struct seniorCitizen *)malloc(1 * sizeof(struct seniorCitizen));
            B = (struct seniorCitizen *)malloc(1 * sizeof(struct seniorCitizen));
            int flag = 0, add;
            while(flag == 0)
            {
                printf("Enter the name for senior citizen for first dose:");
                scanf("%c",&temporary);
                scanf("%[^\n]%*c",&(A->name));
                printf("Enter the center id:");
                scanf("%lld",&(A->center_id));
                printf("To add more press 1 to exit press 0\n");
                scanf("%d",&add);
                if(add == 0)
                {
                    printf("0\n");
                    flag = 1;
                }
                else if(add == 1)
                {
                    printf("1\n");
                    sizeA++;
                    A = realloc(A, sizeA *sizeof(struct seniorCitizen));
                }
            }
            flag = 0;
            while(flag == 0)
            {
                printf("Enter the name for senior citizen for second dose:");
                scanf("%c",&temporary);
                scanf("%[^\n]%*c",&(B->name));
                printf("Enter the center id:");
                scanf("%lld",&(B->center_id));
                printf("To add more press 1 to exit press 0\n");
                scanf("%d",&add);
                if(add == 0)
                {
                    flag = 1;
                }
                else if(add == 1)
                {
                    sizeB++;
                    B = realloc(B, sizeB *sizeof(struct seniorCitizen));
                }
            }
            SeniorCitizenIntersection(A,B,sizeA,sizeB);
            free(A);
            free(B);
        }
        else if(input == 15)
        {
            exit_condition = 1;
        }
        char YorN;
        printf("Do you want to continue? (y/n):");
        scanf("%c",&YorN);
        scanf("%c",&YorN);
        if(YorN == 'n')
        {
            exit_condition = 1;
        }
    }
    // freeing all the variable
    free(beneficiary);
    free(center);
    free(districts);
}
