#include <ofapi/of_api.h>


int main(void)
{
	struct device_node *node;
	struct device_node *tree;
	struct device_node *tmp;
	int x=0;
	void *property=NULL;
	int plen;

	of_init();

	if((node=of_find_node_by_name("pci", 0))) {

		printf("node name is %s, node path is %s\n", node->name, node->path);
		tmp=of_get_parent(node);
		if(tmp) {
			printf("tmp name is %s, tmp path is %s\n", tmp->name, tmp->path);
		}

		property=of_find_property(node, "reg", &plen);
		of_free_node(tmp);
		of_free_node(node);
		free(property);
	}

	node=of_find_node_by_phandle(4287171720);
	if(node) {
		printf("FOUND NODE\n");
		printf("node path is %s\n", node->path);
		printf("node type is %s\n", node->type);
		of_free_node(node);
	}

	while((node = of_find_node_by_name("pci", 1))!=NULL) {
		printf("node path is %s\n", node->path);
		of_free_node(node);
	}

	while((node = of_find_node_by_type("pci", 1))!=NULL) {
		printf("node path is %s\n", node->path);
		of_free_node(node);
	}

	if((node=of_find_node_by_path("/"))){
		printf("node path is %s\n", node->path);
		printf("node type is %s\n", node->type);
		of_free_node(node);
	}

	/* needs a tree_next(thing) */
	tree=of_find_type_devices("pci");
	if(tree) {
		tmp=tree->next;
		while(tmp) {
			printf("(%s) %d - tmp name is %s\n", tmp->type, x++, tmp->name);
			tmp=tmp->next;
		}
	}
	of_find_type_devices_free(tree);

	return EXIT_SUCCESS;
}
