#include <ofapi/of_api.h>

uint64_t total_ram;

uint32_t cells_addr;
uint32_t cells_size;


void calculate_ram(uint8_t * ptr, uint32_t size)
{
	int i = 1;
	int num = 0;
	int status = 1;
	uint64_t size64;
	uint32_t size32;
	uint8_t *p = ptr;
	
	while(status) {

		if((cells_addr == 2) && (cells_size == 1)) 
			i+=2;
		 else
			i++;
				
		if(cells_size == 2) {
			status=of_property_to_n_uint64(&size64, p, size, i++);		
			if(!status)
				break;
			total_ram+=size64;
		} else {
			status=of_property_to_n_uint32(&size32, p, size, i++);
			if(!status)
				break;
							
			total_ram+=size32;						
		}
	}	
}

int main(int argc, char **argv)
{
	struct device_node *node;
	struct device_node *parent;
	int plen = 0;
	void *property;
	
	if(argc == 1)
		of_init();
	else
		of_init_root(argv[1]);
	
	while ((node = of_find_node_by_name("memory", 1)) != NULL) {

		if((parent=of_get_parent(node))) {
					
			if((property = of_find_property(parent,"#address-cells", &plen))) {
				of_property_to_uint32(&cells_addr, property, plen);
				free(property);
			}
			
			if((property = of_find_property(parent,"#size-cells", &plen))) {
				of_property_to_uint32(&cells_size, property, plen);
				free(property);
			}

			property = of_find_property(node, "reg", &plen);
					
			calculate_ram(property, plen);
			
			free(property);
			of_free_node(parent);
		}

		of_free_node(node);
	}

	printf("Total bytes %lld\n", total_ram);
	printf("Total MB %lld\n", total_ram >> 20);
	printf("Total GB %lld\n", total_ram >> 30);

	return EXIT_SUCCESS;
}
