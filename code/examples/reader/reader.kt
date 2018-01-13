import rml.RMLReader


class Reader(source: String?) : RMLReader(source) {
    override fun elementStart(tagName: String, attributes: Map<String, String>) {
        println("elementStart $tagName,attrs $attributes")
    }

    override fun elementEnd(tagName: String) {
        println("elementEnd $tagName")
    }

    override fun commentStart() {
        println("commentStart")
    }

    override fun commentContent(content: String) {
        println("commentContent $content")
    }

    override fun commentEnd() {
        println("commentEnd")
    }

}

fun main(args: Array<String>) {
    val s = readFile("data.xml")
    val reader = Reader(s)
    reader.read()
}