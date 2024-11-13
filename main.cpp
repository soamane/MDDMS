#include "src/frontend/application/application.hpp"

#include "src/backend/database/config/database_config.hpp"
#include "src/backend/database/postgres/postgres_database.hpp"

#include <clocale>
#include <QApplication>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RUS");

    QApplication app(argc, argv);

    DatabaseConfig config("localhost", "medical_db", "postgres", "soa");
    PostgresDatabase database(config);
    {
        database.open();
    }

    MainWindow window;
    window.show();

    return app.exec();
}
