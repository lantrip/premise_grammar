import React from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import {
  createRootRoute,
  createRoute,
  createRouter,
  Router,
} from "@tanstack/react-router";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { RootLayout } from "./routes/__root";
import Dashboard from "./routes/index";
import BeatsPage from "./routes/beats/index";
import FactsPage from "./routes/facts/index";
import EntitiesPage from "./routes/entities/index";
import TimelinePage from "./routes/timeline/index";
import RunPage from "./routes/run/index";

const queryClient = new QueryClient();

const rootRoute = createRootRoute({ component: RootLayout });
const indexRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/",
  component: Dashboard,
});
const beatsRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/beats",
  component: BeatsPage,
});
const factsRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/facts",
  component: FactsPage,
});
const entitiesRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/entities",
  component: EntitiesPage,
});
const timelineRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/timeline",
  component: TimelinePage,
});
const runRoute = createRoute({
  getParentRoute: () => rootRoute,
  path: "/run",
  component: RunPage,
});

const routeTree = rootRoute.addChildren([
  indexRoute,
  beatsRoute,
  factsRoute,
  entitiesRoute,
  timelineRoute,
  runRoute,
]);
const router = createRouter({ routeTree, context: { queryClient } });

declare module "@tanstack/react-router" {
  interface Register {
    router: typeof router;
  }
}

createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <QueryClientProvider client={queryClient}>
      <Router router={router} />
    </QueryClientProvider>
  </React.StrictMode>
);
