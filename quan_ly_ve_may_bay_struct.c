#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int luaChon;
    int i;

    do {
        printf("\n=== HỆ THỐNG BÁN VÉ VÀ CHECK-IN MÁY BAY ===\n");
        printf("1. Thêm vé máy bay mới\n");
        printf("2. Hiển thị danh sách vé\n");
        printf("3. Cập nhật hành lý theo PNR\n");
        printf("4. Xóa vé theo PNR\n");
        printf("5. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &luaChon);
        while (getchar() != '\n');

        switch (luaChon) {
            case 1:
                if (soLuong >= 100) {
                    printf("Danh sách vé đã đầy, không thể thêm mới!\n");
                } else {
                    printf("\nNhập mã PNR: ");
                    scanf("%s", danhSachVe[soLuong].pnrCode);
                    while (getchar() != '\n');

                    printf("Nhập họ tên hành khách: ");
                    fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                    danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';

                    printf("Nhập hạng vé (1-Eco, 2-Deluxe, 3-Business): ");
                    scanf("%d", &danhSachVe[soLuong].ticketClass);

                    printf("Nhập khối lượng hành lý (kg): ");
                    scanf("%f", &danhSachVe[soLuong].baggageWeight);
                    while (getchar() != '\n');

                    if (danhSachVe[soLuong].ticketClass == 3) {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    } else if (danhSachVe[soLuong].baggageWeight > 7.0f) {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                    } else {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    }

                    printf("=> Thêm vé thành công! Cước phạt hành lý quá cân: %.0f VNĐ.\n", danhSachVe[soLuong].baggageFee);
                    soLuong++;
                }
                break;

            case 2:
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                } else {
                    printf("\n========================================================================================\n");
                    printf("%-4s | %-10s | %-25s | %-10s | %-14s | %s\n", "STT", "Mã PNR", "Họ tên hành khách", "Hạng vé", "Hành lý (kg)", "Cước quá cước");
                    printf("========================================================================================\n");
                    for (i = 0; i < soLuong; i++) {
                        char hangVeStr[15];
                        if (danhSachVe[i].ticketClass == 1) {
                            strcpy(hangVeStr, "Eco");
                        } else if (danhSachVe[i].ticketClass == 2) {
                            strcpy(hangVeStr, "Deluxe");
                        } else {
                            strcpy(hangVeStr, "Business");
                        }

                        printf("%-4d | %-10s | %-25s | %-10s | %-14.1f | %.0f VNĐ\n",
                               i + 1,
                               danhSachVe[i].pnrCode,
                               danhSachVe[i].passengerName,
                               hangVeStr,
                               danhSachVe[i].baggageWeight,
                               danhSachVe[i].baggageFee);
                    }
                    printf("========================================================================================\n");
                }
                break;

            case 3:
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                } else {
                    char pnrSua[15];
                    int viTriSua = -1;

                    printf("\nNhập mã PNR cần cập nhật hành lý: ");
                    scanf("%s", pnrSua);
                    while (getchar() != '\n');

                    for (i = 0; i < soLuong; i++) {
                        if (strcmp(danhSachVe[i].pnrCode, pnrSua) == 0) {
                            viTriSua = i;
                            break;
                        }
                    }

                    if (viTriSua != -1) {
                        printf("Tìm thấy hành khách: %s\n", danhSachVe[viTriSua].passengerName);
                        printf("Nhập trọng lượng hành lý mới (kg): ");
                        scanf("%f", &danhSachVe[viTriSua].baggageWeight);
                        while (getchar() != '\n');

                        if (danhSachVe[viTriSua].ticketClass == 3) {
                            danhSachVe[viTriSua].baggageFee = 0.0f;
                        } else if (danhSachVe[viTriSua].baggageWeight > 7.0f) {
                            danhSachVe[viTriSua].baggageFee = (danhSachVe[viTriSua].baggageWeight - 7.0f) * 50000.0f;
                        } else {
                            danhSachVe[viTriSua].baggageFee = 0.0f;
                        }

                        printf("=> Cập nhật thành công! Phí hành lý quá cước mới: %.0f VNĐ.\n", danhSachVe[viTriSua].baggageFee);
                    } else {
                        printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                    }
                }
                break;

            case 4:
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                } else {
                    char pnrXoa[15];
                    int viTriXoa = -1;

                    printf("\nNhập mã PNR cần xóa: ");
                    scanf("%s", pnrXoa);
                    while (getchar() != '\n');

                    for (i = 0; i < soLuong; i++) {
                        if (strcmp(danhSachVe[i].pnrCode, pnrXoa) == 0) {
                            viTriXoa = i;
                            break;
                        }
                    }

                    if (viTriXoa != -1) {
                        for (i = viTriXoa; i < soLuong - 1; i++) {
                            danhSachVe[i] = danhSachVe[i + 1];
                        }
                        soLuong--;
                        printf("=> Đã xóa thành công vé có mã PNR: %s ra khỏi hệ thống.\n", pnrXoa);
                    } else {
                        printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                    }
                }
                break;

            case 5:
                printf("\nCảm ơn bạn đã sử dụng chương trình! Tạm biệt.\n");
                break;

            default:
                printf("Lựa chọn không hợp lệ, vui lòng chọn lại từ 1 đến 5!\n");
                break;
        }
    } while (luaChon != 5);

    return 0;
}
