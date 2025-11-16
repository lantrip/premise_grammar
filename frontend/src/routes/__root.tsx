import { Outlet, Link } from "@tanstack/react-router";

export function RootLayout() {
  return (
    <div className="min-h-screen bg-background text-foreground">
      <header className="border-b">
        <div className="mx-auto max-w-5xl px-4 py-3 flex items-center gap-4">
          <Link to="/">Premise</Link>
          <nav className="ml-auto flex gap-4 text-sm">
            <Link to="/beats">Beats</Link>
            <Link to="/facts">Facts</Link>
            <Link to="/entities">Entities</Link>
            <Link to="/timeline">Timeline</Link>
            <Link to="/run">Run</Link>
          </nav>
        </div>
      </header>
      <main className="mx-auto max-w-5xl px-4 py-6">
        <Outlet />
      </main>
    </div>
  );
}



