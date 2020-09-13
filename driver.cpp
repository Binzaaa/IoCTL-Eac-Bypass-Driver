#include "mem.h"


UNICODE_STRING symbolic_link, device_name;


NTSTATUS control_input_output(PDEVICE_OBJECT device_object, PIRP input_request_p) {
	input_request_p->IoStatus.Status = STATUS_SUCCESS;
	input_request_p->IoStatus.Information = sizeof(info);

	auto stackk = IoGetCurrentIrpStackLocation(input_request_p);

	auto PizdaScooby = (p_info)input_request_p->AssociatedIrp.SystemBuffer; //auto Buffer

	if (stackk) {
		if (PizdaScooby && sizeof(*PizdaScooby) >= sizeof(info)) {
			if (stackk->Parameters.DeviceIoControl.IoControlCode == control_read) {
				if (PizdaScooby->address != nullptr)
				{
					read_mem(PizdaScooby->pid, PizdaScooby->address, PizdaScooby->value, PizdaScooby->size);
				}
				else
				{
					PizdaScooby->value = nullptr;
				}
			}
			else if (stackk->Parameters.DeviceIoControl.IoControlCode == control_write) {
				write_mem(PizdaScooby->pid, PizdaScooby->address, PizdaScooby->value, PizdaScooby->size);
			}
			else if (stackk->Parameters.DeviceIoControl.IoControlCode == control_write_protected) {
				write_memprotected(PizdaScooby->pid, PizdaScooby->address, PizdaScooby->value, PizdaScooby->size);
			}
			else if (stackk->Parameters.DeviceIoControl.IoControlCode == control_base) {

			}
		}
	}
}