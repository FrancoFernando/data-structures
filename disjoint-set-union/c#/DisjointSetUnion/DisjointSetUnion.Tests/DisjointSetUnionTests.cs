using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace DisjointSetUnion.Tests
{

    [TestClass]
    public class DisjointSetUnionTests
    {
        [TestMethod]
        public void InitiallyDisjoint()
        {
            DisjointSetUnion dsu = new DisjointSetUnion(10);

            for (int i = 0; i < 10; ++i) {
                Assert.AreEqual(i, dsu.Find(i));
            }
        }

        [TestMethod]
        public void SimpleUnion()
        {
            DisjointSetUnion dsu = new DisjointSetUnion(10);

            dsu.Unite(0, 1);
            Assert.IsTrue(dsu.Same(0, 1));

            dsu.Unite(2, 3);
            Assert.IsTrue(dsu.Same(2, 3));

            dsu.Unite(4, 5);
            Assert.IsTrue(dsu.Same(4, 5));
        }

        [TestMethod]
        public void ComplexUnion()
        {
            DisjointSetUnion dsu = new DisjointSetUnion(10);

            dsu.Unite(0, 1);
            dsu.Unite(2, 3);
            dsu.Unite(5, 6);
            dsu.Unite(7, 8);
            dsu.Unite(6, 7);
            dsu.Unite(0, 2);

            Assert.IsTrue(dsu.Same(0, 1));  
            Assert.IsTrue(dsu.Same(2, 3));
            Assert.IsTrue(dsu.Same(0, 2));
            Assert.IsTrue(dsu.Same(8, 6));
            Assert.IsFalse(dsu.Same(0, 7));

            dsu.Unite(0, 6);
            Assert.IsTrue(dsu.Same(0, 7));
        }
    }
}
