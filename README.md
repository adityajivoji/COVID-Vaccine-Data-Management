# COVID-Vaccine-Data-Management
CoProtect is a covid vaccination platform available for the citizens of India to book their appointment for vaccination against Covid-19 disease. This project implements this platform using array of structures wherein citizens can register themselves and book an appointment for them to receive the vaccine at the desired centre. This program has mainly two structures to store the data of citizens and the authorized centres.

The structure for citizens contain the following fields:
- 5-digit beneficiary id
- Beneficiary full name
- Gender
- Year of birth
- Number of doses taken (0/1/2)

The structure for the vaccination centre contain the following fields:
- Centre ID
- Centre address
- District
- PIN code
- Center type (government/private) (Only government-run centres are authorized to provide vaccines at free of cost)
- Vaccine types (covaxin/covishield/sputnik/zydus/Pfizer/moderna) that are available with their respective quantity available for the day and the price fixed for each vaccine
type.

facilities to the user.
All the records for centres and beneficiaries are kept in sorted fashion (after any operation) based on centre ID and beneficiary ID respectively.

a. addNewBeneficiary():
  - Input: Beneficiary full name, gender, year of birth (Beneficiary id is unique and system generated number)
  - Output: Display all the information after successful addition of record.

b. addNewCenter():
  - Input: centre ID, address, district, PIN code, centre type, vaccine type with their respective quantity available for the day.
- Output: Display the message after successful addition of record.

c. EnlistSortedCenters ():
  - Input: Key field for the sorted list (Center ID/PIN code/District-wise)
  - Output: Display the sorted list of centres based on key field.

d. getCentre():
  - Input: Parameter for searching the center (Center ID/District/PIN code/center type/vaccine type)
  - Output: Display the list of centers based on search parameter.

e. BookAppointment():
  - Input: Beneficiary ID, Center ID, vaccine type
  - Output – Display the message after a successful booking.

f. CancelAppointment():
  - Input: Beneficiary ID
  - Output: Display the message after a successful cancellation.

g. removeBeneficiary():
  - Input: Beneficiary ID
  - Output: Display the message after the successful removal.

h. removeCentre():
  - Input: Center ID
  - Output: Display the message after the successful removal.

i. UpdateBeneficiaryInfo():
  - Input: Beneficiary ID and the fields to update
  - Output: Display the message after a successful update.

j. UpdateCenterInfo():
  - Input: Center ID and the fields to update
  - Output: Display the message after a successful update.

k. MaxIncomeCentre():
  - Input: None
  - Output: Print the centre information where the maximum income (in Rs.) has been generated.

l. VaccineAvailabilityReport():
  - Input: None
  - Output: Generate a report with list of centres (sorted district-wise) and the number of vaccines available (at any given time) for each vaccine type.

m. DistrictReport():
  - Input: None
  - Output: Total number of vaccines booked in each district.

n. SeniorCitizenIntersection():
  - Input:
    i. List1 - List of all senior citizens (age > 60) who have booked their 1st dose
    ii. List2 – List of senior citizens (age > 60) who have booked their 2nd dose
  - Output: List of senior citizens who booked both dosages at the same centre.
