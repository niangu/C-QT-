#include <QCoreApplication>
#include"handsetsoft.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HandsetBrand *brand;
    brand = new HandsetBrandM();
    brand->SetHandsetSoft(new HandsetGame());
    brand->Run();
    brand->SetHandsetSoft(new HandSetAddressList());
    brand->Run();

    return a.exec();
}
