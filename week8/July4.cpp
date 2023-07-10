template<typename T>
class BST
{
	/* ... */

	/**
	 * Output this tree in a GraphViz DOT representation as a
	 * directed graph ("digraph").
	 *
	 * Calls to this method will cause an entire graph (starting
	 * with "digraph G {") to be output to the given std::ostream.
	 *
	 * @param   o    the output stream to write to
	 */
	void printDot(std::ostream &o) const {
            o << "digraph G {" << std::endl;
            root->printDot(o);
            o << "}" << std::endl;
    }

	

	class Node
	{
		

		/**
		 * Output information about this node in GraphViz DOT format.
		 *
		 * This will output information about this node
		 * (with no graph-level decorations such as "digraph G {")
		 * and recursively descend to its children.
		 */
		void printDot(std::ostream&) const{
            o << id << " [ label = \"" << value << "\" ];" << std::endl;

            if (left != nullptr) {
                o << id << " -> " << left->id << " [ label = \"L\" ];" << std::endl;
                left->printDot(o);
            }

            if (right != nullptr) {
                o << id << " -> " << right->id << " [ label = \"R\" ];" << std::endl;
                right->printDot(o);
            }
        }
	};
};

int main() {
    BST<int> tree;

    


    tree.printDot(std::cout);  // Output the graph to stdout

    return 0;
}