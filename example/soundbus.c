#include <ofapi/of_api.h>




void print_resources(struct device_node *node)
{
	void *property;
	int plen;
	int ranges = 0;
	int x = 0;
	uint32_t start, end;
	int rsrc = 0;
	
	property = of_find_property(node, "reg", &plen);
	if(!property)
		return;
	
	ranges = plen/4;
	
	puts("Resources: ");
	for(x = 1; x <= ranges;x+=2 ) {
	
		of_property_to_n_uint32(&start, property, plen, x);
		of_property_to_n_uint32(&end, property, plen, x+1);
		
		end += start + 0x80000000; start += 0x80000000;
		
		printf(" rsrc[%d] 0x%08x - 0x%08x\n", rsrc++, start, end);
	}

	free(property);
}

void print_model(struct device_node *node)
{
	void *property;
	char *str;
	int plen;
	
	property = of_find_property(node, "model", &plen);
	if(!property)
		return;
	
	str = property;
	str[plen-1] = '\0';
	
	printf("Model: %s\n", str);

	free(property);
}

void print_sound(struct device_node *node)
{
	void *property;
	char *str;
	int plen;
	uint32_t layout_id;
	
	property = of_find_property(node, "compatible", &plen);
	if(!property)
		return;
	
	str = property;
	
	str[plen-1]='\0';
	
	printf("Compatible: %s\n", str);
	
	free(property);
	
	property = of_find_property(node, "layout-id", &plen);
	if(!property)
		return;
		
	of_property_to_int(&layout_id, property, plen);
	
	printf("Layout ID: %d\n", layout_id);
	
	free(property);
}

int main(int argc, char **argv)
{
	struct device_node *root;
	struct device_node *sound;
	struct device_node *soundbus;
	
	if(argc == 1)
		of_init();
	else
		of_init_root(argv[1]);

	if((root = of_find_node_by_path("/")) == NULL) 
		of_error("Could not find node");

	if((sound = of_find_node_by_name("sound", 0)) == NULL) 
		of_error("Could not find sound");
	
	if((soundbus = of_get_parent(sound)) == NULL) 
		of_error("Could not find soundbus");
	
	print_model(root);
	print_sound(sound);
	print_resources(soundbus);

	of_free_node(root);
	of_free_node(sound);
	of_free_node(soundbus);
	
	return EXIT_SUCCESS;
}
