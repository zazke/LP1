#define MAXLEN 100      // fixed length strings

void readRecordsWriteReport();
void writeHeader(char *esp1, char *esp2, char *strfecha);
void readWriteMedicos();
void readWritePacientes();
void readWriteMedicinas(int n);
void writeformattedMedico(char *id, char *name);
void writeformattedPaciente(int i, int dni, char *name);
void writeformattedMedicina(int i, int id, char *name, char *strfecha, int qty);
